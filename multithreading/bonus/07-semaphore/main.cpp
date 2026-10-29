#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <semaphore>
#include <thread>
#include <vector>

int main()
{
    std::counting_semaphore<2> slots(2);

    // Временно забираем оба разрешения: третья попытка не должна ждать.
    slots.acquire();
    slots.acquire();
    const bool extraPermit = slots.try_acquire();
    std::cout << "try_acquire with no permits: " << std::boolalpha << extraPermit << '\n';
    if (extraPermit)
    {
        return 1;
    }
    slots.release(2);

    std::mutex mtx;
    int parked = 0;
    int peak = 0;
    int completed = 0;
    std::vector<std::thread> cars;
    cars.reserve(5);

    for (int id = 1; id <= 5; ++id)
    {
        cars.emplace_back([&, id]() {
            slots.acquire(); // Ждём свободное место, затем забираем разрешение.
            {
                std::lock_guard<std::mutex> guard(mtx);
                ++parked;
                peak = std::max(peak, parked);
                std::cout << "Car " << id << " entered; parked: " << parked << '\n';
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            {
                std::lock_guard<std::mutex> guard(mtx);
                --parked;
                ++completed;
                std::cout << "Car " << id << " left; parked: " << parked << '\n';
            }
            slots.release(); // Возвращаем место следующей машине.
        });
    }

    for (std::thread& car : cars)
    {
        car.join();
    }
    std::cout << "Completed: " << completed << "; peak parked: " << peak << '\n';
    return completed == 5 && parked == 0 && peak <= 2 ? 0 : 1;
}
