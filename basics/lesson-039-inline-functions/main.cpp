// C++98 — inline-функция; встраивание не гарантируется.
#include <iostream>

#include "../../common/console.hpp"
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
