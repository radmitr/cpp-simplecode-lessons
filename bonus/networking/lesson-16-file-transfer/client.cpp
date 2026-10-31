#include "../common/net.hpp"
#include "../common/crc32.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        if (argc > 3) throw std::runtime_error("Usage: client [port] [input-file]");
        const auto port = argc >= 2 ? net::parsePort(argv[1]) : 42016;
        std::string name = "demo.bin";
        std::string bytes(131072, '\0');
        for (std::size_t i = 0; i < bytes.size(); ++i) bytes[i] = static_cast<char>(i % 256);
        if (argc == 3)
        {
            const std::filesystem::path path(argv[2]);
            name = path.filename().string();
            std::ifstream input(path, std::ios::binary | std::ios::ate);
            if (!input) throw std::runtime_error("cannot open input file");
            const auto size = input.tellg();
            if (size < 0 || size > 1024 * 1024)
                throw std::runtime_error("input file exceeds the 1 MiB demo limit");
            bytes.resize(static_cast<std::size_t>(size));
            input.seekg(0);
            if (!bytes.empty()) input.read(bytes.data(), static_cast<std::streamsize>(bytes.size()));
            if (!input) throw std::runtime_error("input file read failed");
        }
        auto socket = net::connectLoopback(static_cast<std::uint16_t>(port),
                                           net::after(std::chrono::seconds(2)));
        const auto deadline = net::after(std::chrono::seconds(5));
        const auto crc = transfer::crc32(bytes);
        net::sendFrame(socket, name, deadline);
        const std::uint32_t metadata[2]{
            htonl(static_cast<std::uint32_t>(bytes.size())), htonl(crc)
        };
        net::sendAll(socket, {reinterpret_cast<const char*>(metadata), sizeof(metadata)}, deadline);
        for (std::size_t sent = 0; sent < bytes.size();)
        {
            const auto count = std::min<std::size_t>(4096, bytes.size() - sent);
            net::sendAll(socket, std::string_view(bytes).substr(sent, count), deadline);
            sent += count;
            if (sent % 32768 == 0 || sent == bytes.size())
                std::cout << "Sent bytes: " << sent << '/' << bytes.size() << '\n';
        }
        const auto reply = net::receiveLine(socket, deadline);
        if (reply != "STORED " + std::to_string(crc))
            throw std::runtime_error("server did not confirm file validation");
        std::cout << "File confirmed: " << bytes.size() << " bytes; CRC32 " << crc << '\n';
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
