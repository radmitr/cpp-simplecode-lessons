// C++98 — char и вывод кодов символов.
#include <cstddef>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    for (size_t i = 0; i < 256; i++)
    {
        cout << "code = " << i << "\t" << (char)i << endl;
    }

    return 0;
}
