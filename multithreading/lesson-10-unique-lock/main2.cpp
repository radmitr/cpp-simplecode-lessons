#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::mutex mtx;

constexpr auto pauseDuration = std::chrono::milliseconds(500);
constexpr auto rowDuration = std::chrono::milliseconds(50);

void pause()
{
    std::this_thread::sleep_for(pauseDuration);
}

void printChars(char ch)
{
    for (int row = 0; row < 3; ++row)
    {
        std::cout << std::string(10, ch) << std::endl;
        std::this_thread::sleep_for(rowDuration);
    }
}

void printLockImmediately(char ch)
{
    std::unique_lock<std::mutex> lock(mtx);
    pause(); // Мьютекс занят во время паузы.
    printChars(ch);
}

void printLockAfterPause(char ch)
{
    pause(); // Оба потока могут ждать одновременно.
    std::unique_lock<std::mutex> lock(mtx);
    printChars(ch);
}

void printDeferred(char ch)
{
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    pause(); // Объект lock уже существует, но мьютекс ещё свободен.
    lock.lock();
    printChars(ch);
}

void printUnlockEarly(char ch)
{
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    pause();
    lock.lock();
    printChars(ch);
    std::cout << ch << ": releasing mutex before the last pause\n";
    lock.unlock();
    pause(); // Последняя пауза проходит без мьютекса.
}

void runPair(const char* title, void (*print)(char))
{
    std::cout << "\n" << title << '\n';
    const auto start = std::chrono::steady_clock::now();

    std::thread first(print, '*');
    std::thread second(print, '#');
    first.join();
    second.join();

    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
    std::cout << "Elapsed: " << elapsed.count() << " ms\n";
}

int main()
{
    runPair("1. Lock immediately, then pause", printLockImmediately);
    runPair("2. Pause, then lock", printLockAfterPause);
    runPair("3. Defer lock, pause, then lock", printDeferred);
    runPair("4. Defer lock, print, unlock, then pause", printUnlockEarly);
}
