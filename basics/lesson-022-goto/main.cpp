// C++98 — переход goto и метки.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

int main()
{
    console::setupConsoleEncoding();

    cout << "Один" << endl;

    goto link;

    cout << "Два" << endl;
    cout << "Три" << endl;

link:
    cout << "Четыре" << endl;
    cout << "Пять" << endl;

    return 0;
}
