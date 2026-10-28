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
    void operator()()
    {
        cout << "Я функтор " << count << endl;
        count++;
    }

private:
    int count = 0;
};

int main(void)
{
    setupConsoleEncoding();

    MyFunctor f;

    for (size_t i = 0; i < 5; i++)
    {
        f();
    }

    return 0;
}
