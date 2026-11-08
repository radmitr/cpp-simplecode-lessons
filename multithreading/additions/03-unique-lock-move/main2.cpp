// C++11 — перемещение std::unique_lock.
#include <iostream>
#include <mutex>

int main()
{
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    const bool before = lock.owns_lock();
    lock.lock();
    const bool during = lock.owns_lock();
    lock.unlock();
    const bool stillAssociated = lock.mutex() == &mtx;

    lock.lock();
    std::mutex* raw = lock.release(); // Отключает unique_lock, но не отпускает mtx.
    const bool detached = lock.mutex() == nullptr && !lock.owns_lock();
    raw->unlock(); // Теперь освобождение обязан выполнить сам текущий поток.

    std::cout << std::boolalpha
              << "Owns after defer: " << before << '\n'
              << "Owns after lock: " << during << '\n'
              << "Associated after unlock: " << stillAssociated << '\n'
              << "Detached after release: " << detached << '\n';
    return !before && during && stillAssociated && detached ? 0 : 1;
}
