// C++20 — std::binary_semaphore и передача сигнала.
#include <iostream>
#include <semaphore>
#include <thread>

int main()
{
    std::binary_semaphore ready(0); // Никто не сможет пройти до release().
    int payload = 0;
    std::thread receiver([&]() {
        ready.acquire();
        // release -> успешный acquire обеспечивает видимость предыдущей записи.
        std::cout << "Received: " << payload << '\n';
    });
    payload = 42;
    ready.release(); // main ничего не acquire-ил: семафор не хранит владельца.
    receiver.join();
    std::cout << "Supported maximum: " << std::counting_semaphore<2>::max() << '\n';
    return payload == 42 ? 0 : 1;
}
