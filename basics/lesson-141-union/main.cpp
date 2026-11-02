// C++98 — объединения union.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

union MyUnion
{
    short int a;
    int b;
    float c;
};

void printMyUnion(MyUnion u)
{
    cout << "a = " << u.a << endl;
    cout << "b = " << u.b << endl;
    cout << "c = " << u.c << endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    MyUnion u;

    u.a = 5;
    printMyUnion(u);
    cout << endl;

    u.b = 175000;
    printMyUnion(u);
    cout << endl;

    u.c = 43.54;
    printMyUnion(u);
    cout << endl;

    return 0;
}
