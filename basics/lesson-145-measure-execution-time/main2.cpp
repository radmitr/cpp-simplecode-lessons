// C++11 — измерение времени через std::chrono.
#include <cstddef>
#include <iostream>
#include <chrono>

#include "../../common/console.hpp"

class SimpleTimer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
public:
    SimpleTimer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~SimpleTimer()
    {
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        std::cout << "DURATION: " << duration.count() << "s" << std::endl;
    }
};

void Foo()
{
    SimpleTimer st;

    for (size_t i = 0; i < 5000; i++)
    {
        std::cout << i << std::endl;
    }
}

int main(void)
{
    console::setupConsoleEncoding();

    Foo();
    return 0;
}
