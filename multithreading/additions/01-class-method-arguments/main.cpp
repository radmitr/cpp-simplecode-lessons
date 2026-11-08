// C++11 — std::thread, std::ref и захваты лямбда-выражений.
#include <functional>
#include <iostream>
#include <thread>

struct MyClass
{
    int total = 0;

    void doWork2(int value)
    {
        total += value;
    }
};

int main()
{
    MyClass m;
    std::thread a(&MyClass::doWork2, m, 123); // Поток хранит копию m.
    a.join();
    const int afterCopy = m.total;
    std::cout << "After copy: " << afterCopy << '\n';

    std::thread b(&MyClass::doWork2, std::ref(m), 123);
    b.join();
    const int afterReference = m.total;
    std::cout << "After std::ref: " << afterReference << '\n';

    std::thread c([&m]() { m.doWork2(123); });
    c.join();
    std::cout << "After lambda: " << m.total << '\n';
    // Каждый поток присоединён до следующего изменения/чтения m.total.
    return afterCopy == 0 && afterReference == 123 && m.total == 246 ? 0 : 1;
}
