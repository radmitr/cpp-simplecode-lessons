// C++11 — std::thread и std::mutex; C++20 — std::counting_semaphore.
#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <semaphore>
#include <thread>
#include <vector>

int main()
{
    // <2>: поддерживаемый максимум не меньше 2; (2): сейчас свободны 2 места.
    std::counting_semaphore<2> slots(2);
    slots.acquire();
    slots.acquire();
    const bool extraPermit = slots.try_acquire(); // Не ждёт; разрешений уже нет.
    // boolalpha меняет печать bool на этом потоке вывода: false вместо 0.
    std::cout << "try_acquire with no permits: " << std::boolalpha << extraPermit << '\n';
    if (extraPermit)
    {
        return 1;
    }
    slots.release(2); // Возвращаем два разрешения, взятые в начале main.

    std::mutex mtx;
    int parked = 0;    // Текущее число зарегистрированных въездов без выезда.
    int peak = 0;      // Наибольшее значение parked за всё время.
    int completed = 0; // Сколько машин закончило работу.
    std::vector<std::thread> cars;
    cars.reserve(5); // Только память для 5 объектов; size() пока 0, потоков ещё нет.

    for (int id = 1; id <= 5; ++id)
    {
        // Создаёт std::thread прямо в vector и запускает лямбду.
        // id копируется для этой машины; используемые общие объекты — по ссылке.
        cars.emplace_back([&, id]() {
            slots.acquire(); // При нуле ждём, при успехе забираем одно разрешение.
            // Между acquire() и lock другой допущенный поток тоже может работать.
            {
                std::lock_guard<std::mutex> guard(mtx);
                ++parked;
                peak = std::max(peak, parked); // max выбирает большее; присваивание сохраняет.
                std::cout << "Car " << id << " entered; parked: " << parked << '\n';
            } // guard отпустил mutex; разрешение семафора остаётся у машины.

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            {
                std::lock_guard<std::mutex> guard(mtx);
                --parked;
                ++completed;
                std::cout << "Car " << id << " left; parked: " << parked << '\n';
            } // Счётчики обновлены, mutex отпущен.
            slots.release(); // Теперь следующая машина может получить место.
        });
    }
    for (std::thread& car : cars)
    {
        car.join(); // Ждём все машины до чтения итогов и уничтожения vector<thread>.
    }

    std::cout << "Completed: " << completed << "; peak parked: " << peak << '\n';
    return completed == 5 && parked == 0 && peak <= 2 ? 0 : 1;
}
