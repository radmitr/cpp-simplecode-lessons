// C++17 — string_view и литерал sv.
#include <exception>
#include <iostream>
#include <string>
#include <string_view>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        using namespace std::literals::string_view_literals;
        std::string owner = "name=Ada";
        std::string_view view(owner);
        const auto split = view.find('=');
        check(split != std::string_view::npos, "delimiter");
        view.remove_prefix(split + 1);
        check(view == "Ada" && owner == "name=Ada", "view changes only its boundaries");
        owner[5] = 'E';
        check(view == "Eda", "shared character storage");
        std::string independent(view);
        owner[5] = 'A';
        check(independent == "Eda" && view == "Ada", "owning copy");
        const auto binary = "a\0b"sv;
        check(binary.size() == 3 && std::string_view("a\0b").size() == 1, "length and terminator");
        std::cout << view << ' ' << independent << ' ' << binary.size() << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
