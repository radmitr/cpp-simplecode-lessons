// C++98 — пользовательские исключения, порядок catch и catch (...); C++11 — noexcept.
#include <stdexcept>
#include "../../../basics/bonus/common/check.hpp"

class ParseError : public std::runtime_error
{
    int line_;
public:
    explicit ParseError(int line) : std::runtime_error("invalid record"), line_(line) {}
    int line() const noexcept { return line_; } // noexcept — C++11.
};

int main()
{
    int caught = 0;
    try { throw ParseError(12); }
    catch (const ParseError& error) // Более конкретный тип перед базовым.
    {
        ++caught;
        std::cout << error.what() << "; line: " << error.line() << '\n';
    }
    catch (const std::exception&) { return 1; }
    try { throw 7; } // Язык разрешает; для прикладных ошибок лучше тип с описанием.
    catch (const std::exception&) { return 1; } // int не наследует exception.
    catch (...) { ++caught; std::cout << "non-standard exception caught\n"; }
    check(caught == 2, "wrong catch");
    std::cout << "OK custom-exceptions\n";
}
