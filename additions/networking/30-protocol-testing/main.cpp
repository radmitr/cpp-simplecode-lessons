// C++17 — string_view; протокол — инкрементальный декодер кадра с ограничением длины.
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

class Decoder
{
    std::string pending_;
    static constexpr std::size_t limit = 64;
public:
    std::vector<std::string> feed(std::string_view bytes)
    {
        std::vector<std::string> frames;
        for (const char byte : bytes)
        {
            pending_ += byte;
            if (pending_.size() < 4) continue;
            std::uint32_t length = 0;
            for (int i = 0; i < 4; ++i) length = (length << 8) | static_cast<unsigned char>(pending_[i]);
            if (length > limit) throw std::runtime_error("frame exceeds limit");
            if (pending_.size() == 4 + length)
            {
                frames.push_back(pending_.substr(4));
                pending_.clear();
            }
        }
        return frames;
    }
    void eof() const { if (!pending_.empty()) throw std::runtime_error("truncated frame"); }
};
int main()
{
    try
    {
        const std::string packet = std::string("\x00\x00\x00\x03", 4) + std::string("a\0b", 3);
        for (std::size_t split = 0; split <= packet.size(); ++split)
        {
            Decoder decoder;
            auto frames = decoder.feed(std::string_view(packet).substr(0, split));
            auto rest = decoder.feed(std::string_view(packet).substr(split));
            frames.insert(frames.end(), rest.begin(), rest.end());
            check(frames == std::vector<std::string>{std::string("a\0b", 3)}, "every split point");
            decoder.eof();
        }
        Decoder combined;
        check(combined.feed(packet + packet).size() == 2, "coalesced frames");
        for (const auto data : {std::string("\x00\x00\x00\x41", 4), packet.substr(0, 5)})
        {
            bool rejected = false;
            try { Decoder decoder; decoder.feed(data); decoder.eof(); }
            catch (const std::runtime_error&) { rejected = true; }
            check(rejected, "oversize or truncated input");
        }
        std::cout << "8 split points; coalescing; invalid input\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
