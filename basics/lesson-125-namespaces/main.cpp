// C++98 — пространства имён namespace.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

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
