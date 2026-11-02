// C++98 — составные операторы присваивания.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

int main()
{
    console::setupConsoleEncoding();

    // =1=
    int a = 0;
    a++;
    a--;

    // =2=
    a = a + 20;
    a += 20;

    a = a - 10;
    a -= 10;

    a = a * 2;
    a *= 2;

    a = a / 2;

    a /= 2;

    return 0;
}
