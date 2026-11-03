// C++98 — переход goto и метки.
#include <iostream>

#include "../../common/console.hpp"

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
