#include <iostream>
#include <chrono>

void setupConsoleEncoding()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
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
