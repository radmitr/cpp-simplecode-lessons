// C++98 — main() и вывод последовательности сообщений.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int main()
{
    console::setupConsoleEncoding();

    cout << "Один" << endl;
    cout << "Два" << endl;
    cout << "Три" << endl;
    cout << "Четыре" << endl;
    cout << "Пять" << endl;

    return 0;
}
