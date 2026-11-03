// C++98 — предикаты и стандартные алгоритмы; C++11 — списковая инициализация.
#include <algorithm>
#include <iostream>
#include <vector>

#include "../../common/console.hpp"

//using namespace std;

bool greaterThenZero(int a)
{
    return a > 0;
}

bool lessThenZero(int a)
{
    return a < 0;
}

bool equalZero(int a)
{
    return a == 0;
}

int main(void)
{
    console::setupConsoleEncoding();

    std::vector<int> v{5, -40, 43, -12, 6, -95, -50, 0};

    int result = std::count_if(v.begin(), v.end(), greaterThenZero);
    int result2 = std::count_if(v.begin(), v.end(), lessThenZero);
    int result3 = std::count_if(v.begin(), v.end(), equalZero);

    std::cout << "greaterThenZero: " << result << std::endl;
    std::cout << "lessThenZero: " << result2 << std::endl;
    std::cout << "equalZero: " << result3 << std::endl;

    return 0;
}
