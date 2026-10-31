#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::istringstream input("10 20 bad 30");
    int value = 0;
    while (input >> value)
    {
        std::cout << "number: " << value << '\n';
    }

    std::cout << std::boolalpha;
    std::cout << "fail: " << input.fail() << ", eof: " << input.eof() << '\n';

    // clear() сбрасывает флаги, но не удаляет ошибочный токен из потока.
    input.clear();
    std::string invalidToken;
    input >> invalidToken;
    std::cout << "skipped: " << invalidToken << '\n';

    while (input >> value)
    {
        std::cout << "number: " << value << '\n';
    }
    std::cout << "fail: " << input.fail() << ", eof: " << input.eof() << '\n';

    // EOF после последней успешной операции не отменяет прочитанное значение.
    std::istringstream lastNumber("42");
    if (lastNumber >> value)
    {
        std::cout << "last: " << value << ", eof: " << lastNumber.eof()
                  << ", fail: " << lastNumber.fail() << '\n';
    }
}
