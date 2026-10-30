#include <iostream>
#include <thread>

// Намеренно неверный пример: два потока меняют общий int без синхронизации.
// Гонка данных означает неопределённое поведение, а не только потерю прибавлений.
int main()
{
    std::cout << "Intentional data race: undefined behavior.\n";

    int counter = 0;
    auto increment = [&]() {
        for (int i = 0; i < 100000; ++i)
        {
            ++counter; // Оба потока изменяют обычный int без синхронизации.
        }
    };

    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();

    // join() ожидает завершения, но не исправляет гонку во время работы.
    std::cout << "Expected: 200000\nObserved (undefined behavior): " << counter << '\n';
}
