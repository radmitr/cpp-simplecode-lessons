// C++98 — защита заголовков от повторного включения.
#include <iostream>

#include "../../../common/console.hpp"
#include "bar.h"
#include "foo.h"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    foo();
    std::cout << std::endl;
    bar();

    return 0;
}
