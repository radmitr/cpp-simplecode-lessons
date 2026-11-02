// C++20 — std::jthread и совместная остановка через std::stop_token.
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
                // Здесь пишет только worker. main прочитает после его завершения.
                ++completed;
            }
        }); // Конструктор запускает поток; main продолжает работу параллельно.

        std::this_thread::sleep_for(std::chrono::milliseconds(350));
        worker.request_stop(); // Устанавливает признак остановки, не прерывает сон.
    } // ~jthread(): если joinable(), request_stop(), затем join(); main ждёт здесь.

    // Автоматический join уже закончился: worker больше не меняет completed.
    std::cout << "Worker stopped; completed iterations: " << completed << '\n';
}
