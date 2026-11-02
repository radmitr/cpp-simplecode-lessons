// C++20 — std::binary_semaphore::try_acquire_for() и try_acquire_until().
#include <chrono>
#include <iostream>
#include <semaphore>

int main()
{
    std::binary_semaphore signal(0);
    const bool withinDuration = signal.try_acquire_for(std::chrono::milliseconds(10));
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
    const bool beforeDeadline = signal.try_acquire_until(deadline);
    std::cout << std::boolalpha << "try_acquire_for: " << withinDuration << '\n'
              << "try_acquire_until: " << beforeDeadline << '\n';
    signal.release();
    signal.acquire(); // Разрешение есть: acquire его заберёт.
    return !withinDuration && !beforeDeadline ? 0 : 1;
}
