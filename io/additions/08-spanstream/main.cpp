// C++23 — ospanstream и ispanstream; C++20 — span.
#include <array>
#include <exception>
#include <iostream>
#include <span>
#include <spanstream>
#include <string_view>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::array<char, 32> storage{};
        std::ospanstream output{std::span<char>(storage)};
        output << 7 << ' ' << 2.5;
        check(bool(output), "buffer output");
        const auto bytes = output.span();
        check(std::string_view(bytes.data(), bytes.size()) == "7 2.5", "written extent");
        std::ispanstream input{std::span<const char>(bytes.data(), bytes.size())};
        int id = 0; double score = 0;
        input >> id >> score;
        check(bool(input) && id == 7 && score == 2.5, "buffer parsing");
        std::cout << id << ' ' << score << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
