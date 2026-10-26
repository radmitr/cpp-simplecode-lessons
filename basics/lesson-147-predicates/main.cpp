#include <iostream>
#include <vector>
#include <algorithm>

//using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
#endif
}

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
    setupConsoleEncoding();

    std::vector<int> v{5, -40, 43, -12, 6, -95, -50, 0};

    int result = std::count_if(v.begin(), v.end(), greaterThenZero);
    int result2 = std::count_if(v.begin(), v.end(), lessThenZero);
    int result3 = std::count_if(v.begin(), v.end(), equalZero);

    std::cout << "greaterThenZero: " << result << std::endl;
    std::cout << "lessThenZero: " << result2 << std::endl;
    std::cout << "equalZero: " << result3 << std::endl;

    return 0;
}
