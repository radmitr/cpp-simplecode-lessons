// C++98 — защита заголовков от повторного включения.
#include <iostream>
#include "foo.h"
#include "bar.h"

#include "../../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    foo();
    std::cout << std::endl;
    bar();

    return 0;
}
