// C++20 — weak_ordering и согласованный operator==.
#include <compare>
#include <cstddef>
#include <exception>
#include <iostream>
#include <string>

#include "../../../basics/additions/common/check.hpp"

struct Word
{
    std::string text;
    static std::string normalized(std::string value)
    {
        // Для этого примера определены только латинские буквы ASCII.
        for (char& c : value) if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
        return value;
    }
    std::weak_ordering operator<=>(const Word& other) const
    {
        return normalized(text) <=> normalized(other.text);
    }
    bool operator==(const Word& other) const { return (*this <=> other) == 0; }
};

int main()
{
    try
    {
        const Word first{"Ada"};
        const Word second{"ada"};
        check(first == second && (first <=> second) == std::weak_ordering::equivalent, "equivalence by selected property");
        check(first.text != second.text, "observable spelling differs");
        check(Word{"abc"} < Word{"abd"}, "case-insensitive ordering");
        std::cout << first.text << ' ' << second.text << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
