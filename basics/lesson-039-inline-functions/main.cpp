// C++98 — inline-функция; встраивание не гарантируется.
#include "../../common/console.hpp"
#include <iostream>
using namespace std;

inline int Sum_a(int a, int b)
{
    return a + b;
}

int main()
{
    console::setupConsoleEncoding();
    Sum_a(1, 2);
    return 0;
}
