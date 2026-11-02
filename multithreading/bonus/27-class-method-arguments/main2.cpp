// C++11 — std::cref и передача const-ссылки в поток.
#include <functional>
#include <iostream>
#include <thread>

struct Settings { int value = 42; };

int main()
{
    Settings settings;
    int received = 0;
    auto read = [&received](const Settings& source) { received = source.value; };
    std::thread worker(read, std::cref(settings));
    worker.join(); // settings живёт до завершения функции потока.
    std::cout << "Read through cref: " << received << "; original: " << settings.value << '\n';
    return received == 42 && settings.value == 42 ? 0 : 1;
}
