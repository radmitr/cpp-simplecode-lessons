// C++98 — числовые преобразования и static_cast.
#include <iostream>

int main()
{
    int whole = 5;
    double widened = whole;
    double fraction = 2.75;
    int truncated = (int)fraction; // Синтаксис C-style из исходной темы.
    int explicitValue = static_cast<int>(fraction);
    std::cout << widened << ' ' << truncated << ' ' << explicitValue << '\n';
    std::cout << "OK moved-example-061\n";
}
