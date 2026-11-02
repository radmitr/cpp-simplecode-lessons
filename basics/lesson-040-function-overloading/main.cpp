// C++98 — перегрузка функций.
#include "../../common/console.hpp"
#include <iostream>
using namespace std;

int Sum(int a, int b)
{
    return a + b;
}

double Sum(double a, double b)
{
    return a + b;
}

int Sum(int a, int b, int c)
{
    return a + b + c;
}

int main()
{
    console::setupConsoleEncoding();
    cout << "Перегрузка 1: " << Sum(1, 2) << endl;
    cout << "Перегрузка 2: " << Sum(10.5, 5.1) << endl;
    cout << "Перегрузка 3: " << Sum(2, 3, 7) << endl;
    return 0;
}
