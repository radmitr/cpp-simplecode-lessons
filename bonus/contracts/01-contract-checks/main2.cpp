// C++26 — обработчик нарушения контракта и наблюдаемая семантика.
#include <contracts>
#include <exception>
#include <iostream>

#include "../../../basics/bonus/common/check.hpp"

int violations = 0;
void handle_contract_violation(const std::contracts::contract_violation&)
{
    ++violations;
}
int keep_value(int x) pre(x > 0) { return x; }

int main(int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        check(keep_value(1) == 1 && violations == 0, "valid input");
        if (argc == 2)
        {
            check(keep_value(-1) == -1 && violations >= 1, "observed violation");
        }
        std::cout << "violations: " << violations << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
