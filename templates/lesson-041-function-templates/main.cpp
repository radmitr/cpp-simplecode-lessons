// C++98 — шаблоны функций.
#include <iostream>

#include "../../common/console.hpp"
using namespace std;

template <typename T>
T SumT(T a, T b)
{
    return a + b;
}
template <typename T1, typename T2>
T1 SumT_t(T1 a, T2 b)
{
    return a + b;
}
template <typename T1, typename T2>
void Ft(T1 a, T2 b)
{
    cout << "Ft: " << a << endl;
    cout << "Ft: " << b << endl;
    cout << endl;
}
template <class T>  // "class" OR "typename"
void Ft_t(T a)
{
    cout << "Ft_t: " << a << endl;
    cout << endl;
}

int main()
{
    console::setupConsoleEncoding();
    // шаблон 1
    cout << "SumT (1): " << SumT(1, 2) << endl;
    cout << "SumT (2): " << SumT(10.2, 5.05) << endl;

    // шаблон 2
    cout << "SumT_t (1): " << SumT_t(5, 10.4) << endl;
    cout << "SumT_t (2): " << SumT_t(10.5, 7) << endl;

    // шаблон 3
    cout << endl;
    Ft(2.5, 3.5);
    Ft(10, 5.4);
    Ft(2, 3);
    Ft(10.5, 7);

    // шаблон 4
    Ft_t(10);
    return 0;
}
