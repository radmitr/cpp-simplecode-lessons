// C++11 — захваты лямбда-выражений.
#include <iostream>
#include <functional>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    auto f = []()->int {
        return 1.45;
    };

    f();

    function<float()> f2 = []() {
        return 1.45;
    };

    f2();

    function<float()> f3 = []()->int {
        return 1.45;
    };

    f3();

    return 0;
}
