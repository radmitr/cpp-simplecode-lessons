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

enum Speed
{
    MIN = 150,
    RECOMMEND = 600,
    MAX = 800
};

int main(void)
{
    setupConsoleEncoding();

    cout << Speed::MIN << endl;
    cout << Speed::RECOMMEND << endl;
    cout << Speed::MAX << endl;

    Speed speed = Speed::MAX;
    cout << speed << endl;

    return 0;
}
