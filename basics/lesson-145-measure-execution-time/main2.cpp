#include <iostream>
#include <chrono>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

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
    setupConsoleEncoding();

    Foo();
    return 0;
}
