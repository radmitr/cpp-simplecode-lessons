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
