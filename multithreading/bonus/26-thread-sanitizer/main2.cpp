#include <iostream>
#include <thread>

// Намеренно неверный пример для диагностики ThreadSanitizer.
// Запускайте под TSan на Linux/WSL; обычная сборка тоже содержит UB.
int main()
{
    constexpr int iterations = 100000;
    std::cout << "Intentional data race: undefined behavior.\n";
    int counter = 0;
    auto increment = [&]() {
        for (int i = 0; i < iterations; ++i)
        {
            ++counter; // Конфликтующие обращения к обычному int без синхронизации.
        }
    };

    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Expected: " << iterations * 2
              << "\nObserved (undefined behavior): " << counter << '\n';
    // Даже правильное число не доказывает отсутствия гонки.
}
