// C++26 — pre/post и обработчик нарушения (экспериментальная поддержка GCC).
#include <array>
#include <contracts>
#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "../../../basics/additions/common/check.hpp"

std::array<char, 32> events{};
std::size_t count = 0;
void record(char event) noexcept { if (count < events.size()) events[count++] = event; }
void handle_contract_violation(const std::contracts::contract_violation&) { record('V'); }
struct Local { ~Local() { record('D'); } };
int compute(const bool allowed, const bool fail) pre(allowed) post(result: result > 0)
{
    Local local;
    record('B');
    if (fail) throw std::runtime_error("body failed");
    return 0;
}
int main()
{
    try
    {
        compute(false, false);
        const std::string normal(events.data(), count);
        count = 0;
        try { compute(true, true); }
        catch (const std::runtime_error&) { record('C'); }
        const std::string exceptional(events.data(), count);
        check(normal == "VBDV", "pre, body, destruction, post");
        check(exceptional == "BDC", "no postcondition on exception");
        std::cout << normal << '\n' << exceptional << "\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
