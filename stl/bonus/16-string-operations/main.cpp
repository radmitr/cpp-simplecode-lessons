// C++23 — string/string_view::contains и resize_and_overwrite.
#include <cstddef>
#include <exception>
#include <iostream>
#include <string>
#include <string_view>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        const std::string text = "network.log";
        check(text.contains("work") && text.contains('.') && !text.contains("LOG"), "contains");
        check(std::string_view(text).contains(std::string_view{}) , "empty substring");
        std::string buffer;
        buffer.resize_and_overwrite(4, [](char* data, std::size_t size) noexcept {
            if (size < 3) return std::size_t{0};
            data[0] = 'a'; data[1] = 'b'; data[2] = 'c';
            return std::size_t{3};
        });
        check(buffer == "abc", "written length");
        std::cout << buffer << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
