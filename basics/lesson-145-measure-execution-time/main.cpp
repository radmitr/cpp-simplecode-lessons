#include <iostream>
#include <thread>
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
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
};

int sum(int a, int b)
{
    SimpleTimer st;

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tsum STARTED\t============" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tsum STOPPED\t============" << std::endl;
    return a + b;
}

int main(void)
{
    SimpleTimer st;

    setupConsoleEncoding();

    int result;
    std::thread t([&result]() { result = sum(2, 5); });

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << "\tmain\t" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    t.join();
    std::cout << "sum result: " << result << std::endl;

    return 0;
}
