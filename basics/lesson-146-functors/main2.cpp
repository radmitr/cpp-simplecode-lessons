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

class MyFunctor
{
public:
    int operator()(int a, int b)
    {
        cout << "Я функтор " << endl;
        return a + b;
    }

private:
    int count = 0;
};

int main(void)
{
    setupConsoleEncoding();

    MyFunctor f;

    int result = f(3, 2);

    cout << result << endl;

    return 0;
}
