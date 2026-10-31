#include <functional>
#include <future>
#include <iostream>

int increment(int& value)
{
    return ++value;
}

int main()
{
    int value = 10;
    auto copied = std::async(std::launch::async, [](int local) { return ++local; }, value);
    const int copiedResult = copied.get();
    std::cout << "Copy: original=" << value << ", result=" << copiedResult << '\n';

    auto referenced = std::async(std::launch::async, increment, std::ref(value));
    const int referencedResult = referenced.get();
    // get() дождался записи: теперь main снова может читать value.
    std::cout << "Reference: original=" << value << ", result=" << referencedResult << '\n';
    return copiedResult == 11 && referencedResult == 11 && value == 11 ? 0 : 1;
}
