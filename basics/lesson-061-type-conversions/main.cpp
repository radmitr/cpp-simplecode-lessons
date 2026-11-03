// C++98 — преобразование int в char в стиле C.
#include <iostream>

#include "../../common/console.hpp"
using namespace std;

int main()
{
    console::setupConsoleEncoding();
    cout << "\n CHAR = " << sizeof(char) << " byte" << endl;
    cout << endl;

    for (int i = 0; i <= 255; i++)
    {
        cout << "code = " << i << "\t" << "char = " << (char)i << endl;
    }
    return 0;
}
