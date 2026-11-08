// C++11 — std::shared_future.
#include <future>
#include <iostream>

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    auto result = std::async(std::launch::async, sum, 2, 5);
    auto shared = result.share(); // Передаёт доступ; обычный result становится невалидным.
    shared.wait();
    shared.wait();
    const int& first = shared.get();
    const int& second = shared.get();
    std::cout << "Original future valid: " << std::boolalpha << result.valid() << '\n';
    std::cout << "First get: " << first << '\n';
    std::cout << "Second get: " << second << '\n';
    std::cout << "Same stored value: " << (&first == &second) << '\n';
    return !result.valid() && first == 7 && &first == &second ? 0 : 1;
}
