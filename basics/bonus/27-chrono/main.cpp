#include <chrono>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        using namespace std::chrono;
        const auto timeout = 1500ms;
        check(duration_cast<seconds>(timeout).count() == 1, "duration truncation failed");
        check(duration<double>(timeout).count() == 1.5, "fractional conversion failed");
        const auto start = steady_clock::now();
        const auto elapsed = steady_clock::now() - start;
        check(elapsed >= steady_clock::duration::zero(), "steady clock went backwards");
        std::cout << "milliseconds=" << timeout.count() << '\n';
        std::cout << "OK 27-chrono\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
