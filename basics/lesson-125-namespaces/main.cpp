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

namespace firstNS
{
    void foo()
    {
        cout << "firstNS::foo()" << endl;
    }

    int a;
}

namespace secondNS
{
    void foo()
    {
        cout << "secondNS::foo()" << endl;
    }

    int b;
}

namespace thirdNS
{
    namespace secondNS
    {
        void foo()
        {
            cout << "thirdNS::secondNS::foo()" << endl;
        }
    }

    int c;
}

int main(void)
{
    setupConsoleEncoding();

    firstNS::foo();
    secondNS::foo();
    thirdNS::secondNS::foo();

    cout << "a=" << firstNS::a << endl;
    cout << "b=" << secondNS::b << endl;
    cout << "c=" << thirdNS::c << endl;

    using namespace firstNS;
    //using namespace secondNS;
    foo();

    return 0;
}
