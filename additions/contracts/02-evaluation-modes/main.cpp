// C++26 — контракты и contract_violation (экспериментальная поддержка GCC).
#include <contracts>
#include <cstdio>
#include <exception>
#include <iostream>
#include <string_view>

int violations = 0;
void handle_contract_violation(const std::contracts::contract_violation& violation)
{
    ++violations;
    std::fprintf(stderr, "handler: kind=%d terminating=%d at %s:%u\n",
        static_cast<int>(violation.kind()), violation.is_terminating(),
        violation.location().file_name(), violation.location().line());
    std::fflush(stderr);
}
int echo(const int value) pre(value > 0) { return value; }
int main(int argc, char* argv[])
{
    try
    {
        if (argc > 2 || (argc == 2 && std::string_view(argv[1]) != "--violate")) return 1;
        const int value = echo(argc == 2 ? -1 : 1);
        std::cout << "value=" << value << " violations=" << violations << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
