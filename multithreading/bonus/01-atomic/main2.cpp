#include <iostream>
#include <string_view>
#include <thread>

// Намеренно неверный пример: запускать отдельно с аргументом --unsafe.
// Гонка данных означает неопределённое поведение, а не только потерю прибавлений.
int main(int argc, char* argv[])
{
    if (argc != 2 || std::string_view(argv[1]) != "--unsafe")
    {
        std::cout << "Intentional data race. Run with --unsafe to demonstrate UB.\n";
        return 0;
    }

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
