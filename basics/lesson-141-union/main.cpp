#include <iostream>

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
#endif
}

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
    setupConsoleEncoding();

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
