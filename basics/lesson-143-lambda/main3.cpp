// C++11 — лямбда-выражения.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    auto f = []() {
        return 1.2232;
    };

    auto q = f();

    cout << q << endl;

    return 0;
}
