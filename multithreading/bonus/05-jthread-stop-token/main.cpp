#include <chrono>
#include <iostream>
#include <stop_token>
#include <thread>

int main()
{
    int completed = 0;
    {
        std::jthread worker([&completed](std::stop_token stop) {
            while (!stop.stop_requested())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                ++completed; // completed изменяет только рабочий поток.
            }
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(350));
        worker.request_stop(); // Запрос, а не принудительное прерывание.
        // Выход из блока: деструктор jthread запросит остановку и выполнит join().
    }

    // Автоматический join() уже завершился: теперь результат можно читать.
    std::cout << "Worker stopped; completed iterations: " << completed << '\n';
}
