#include "../common/net.hpp"
#include "../common/crc32.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

namespace fs = std::filesystem;

fs::path newDirectory(const fs::path& root)
{
    fs::create_directories(root);
    std::random_device random;
    for (int attempt = 0; attempt < 10; ++attempt)
    {
        const auto name = "transfer-" + std::to_string(net::Clock::now().time_since_epoch().count())
            + "-" + std::to_string(random());
        const auto path = root / name;
        if (fs::create_directory(path)) return path;
    }
    throw std::runtime_error("cannot create a new transfer directory");
}

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        if (argc > 3) throw std::runtime_error("Usage: server [port] [output-directory]");
        const auto port = argc >= 2 ? net::parsePort(argv[1], true) : 42016;
        // Общие скрипты передают компилятору абсолютный путь исходника.
        const auto project = (fs::path(__FILE__).parent_path() / "../../..").lexically_normal();
        const fs::path root = argc == 3 ? fs::path(argv[2])
            : project / "build/bonus/networking/lesson-16-file-transfer/received";
        auto listener = net::listenTcp(static_cast<std::uint16_t>(port));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        const auto deadline = net::after(std::chrono::seconds(5));
        const auto name = net::receiveFrame(client, deadline);
        if (name.empty() || name.size() > 128 || name == "." || name == ".."
            || name.find_first_of("/\\\r\n") != std::string::npos || name.find('\0') != std::string::npos)
            throw std::runtime_error("invalid file name");
        const auto metadata = net::receiveExact(client, 8, deadline);
        std::uint32_t size = 0, expectedCrc = 0;
        std::memcpy(&size, metadata.data(), 4);
        std::memcpy(&expectedCrc, metadata.data() + 4, 4);
        size = ntohl(size);
        expectedCrc = ntohl(expectedCrc);
        if (size > 1024 * 1024) throw std::runtime_error("file exceeds the 1 MiB demo limit");

        const auto directory = newDirectory(root);
        const auto partial = directory / "payload.part";
        const auto destination = directory / "payload.bin"; // Имя из сети не является путём записи.
        try
        {
            std::ofstream output(partial, std::ios::binary);
            if (!output) throw std::runtime_error("cannot create partial file");
            std::uint32_t received = 0;
            std::uint32_t crc = 0xffffffffu;
            while (received < size)
            {
                const auto count = std::min<std::uint32_t>(4096, size - received);
                const auto block = net::receiveExact(client, count, deadline);
                output.write(block.data(), static_cast<std::streamsize>(block.size()));
                if (!output) throw std::runtime_error("file write failed");
                crc = transfer::updateCrc(crc, block);
                received += count;
                if (received % 32768 == 0 || received == size)
                    std::cout << "Received bytes: " << received << '/' << size << '\n';
            }
            output.close();
            if (!output) throw std::runtime_error("file close failed");
            crc ^= 0xffffffffu;
            if (crc != expectedCrc) throw std::runtime_error("CRC32 mismatch");
            fs::rename(partial, destination); // Новый каталог: существующие файлы не заменяются.
            net::sendAll(client, "STORED " + std::to_string(crc) + '\n', deadline);
            std::cout << "Original name: " << name << "\nStored file: " << destination.string() << '\n';
        }
        catch (...)
        {
            std::error_code ignored;
            fs::remove(partial, ignored); // Только наш частичный файл.
            fs::remove(directory, ignored); // Удалится только пустой каталог.
            throw;
        }
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
