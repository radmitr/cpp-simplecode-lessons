#include <functional>
#include "../common/check.hpp"

struct Counter { int value = 0; void add(int n) { value += n; } void operator()(int n) { add(n); } };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Counter counter;
        std::invoke(&Counter::add, counter, 3);
        check(std::invoke(&Counter::value, counter) == 3, "member invocation failed");
        std::function<void(int)> callback = std::ref(counter);
        callback(2);
        check(counter.value == 5, "reference_wrapper copied state");
        const std::function<void()> empty;
        check(!empty, "empty callback should be detectable");
        std::cout << counter.value << '\n';
        std::cout << "OK 23-callables-and-invoke\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
