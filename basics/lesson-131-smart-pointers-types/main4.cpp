// C++11 — std::shared_ptr.
#include <iostream>
#include <memory>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    shared_ptr<int> p1(new int(5));
    shared_ptr<int> p2(p1);

    return 0;
}
