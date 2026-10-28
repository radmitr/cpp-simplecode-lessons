#include <iostream>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

//using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
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
