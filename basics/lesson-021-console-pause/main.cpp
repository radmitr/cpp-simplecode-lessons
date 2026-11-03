// C++98 — ожидание ввода через std::cin.get().
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

    // -1-
    cout << "Нажмите Enter для завершения..." << endl;
    cin.get();

    // -2-
    //int a;
    //cin >> a;

    //-3-
    //cin.get();

    return 0;
}
