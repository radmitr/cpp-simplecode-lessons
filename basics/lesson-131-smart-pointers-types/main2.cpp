// C++98 — std::auto_ptr (устарел в C++11, удалён из стандарта C++17).
#include <iostream>
#include <memory>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    // auto_ptr is deprecated
    auto_ptr<int> p1(new int(5));
    auto_ptr<int> p2(p1);

    return 0;
}
