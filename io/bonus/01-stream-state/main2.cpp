#include <iostream>
#include <limits>
#include <string>

int main()
{
    int count = 0;
    while (true)
    {
        std::cout << "Enter a nonnegative count: ";
        if (std::cin >> count)
        {
            if (count >= 0)
            {
                break;
            }
        }
        else
        {
            // На EOF или ошибке устройства повторять запрос бессмысленно.
            if (std::cin.eof() || std::cin.bad())
            {
                std::cerr << "Input ended\n";
                return 1;
            }
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Try again\n";
    }

    // Удаляем остаток строки после числа перед переходом к getline.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter a label: ";
    std::string label;
    if (!std::getline(std::cin, label))
    {
        std::cerr << "Label is missing\n";
        return 1;
    }
    std::cout << "count: " << count << ", label: " << label << '\n';
}
