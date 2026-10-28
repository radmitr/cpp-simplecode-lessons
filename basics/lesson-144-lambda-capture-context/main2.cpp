#include <iostream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

class MyClass
{
public:
    int a = 11;

    void msg()
    {
        cout << "msg" << endl;
    }

    void lambda()
    {
        auto f = [this]() {
            this->msg();
        };
        f();
    }
};

int main(void)
{
    setupConsoleEncoding();

    MyClass m;

    m.lambda();

    return 0;
}
