// C++98 — вложенные циклы.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/* вложенные циклы */

int main()
{
    console::setupConsoleEncoding();

    for (int i = 1; i < 5; i++)
    {
        cout << "сработал 1-й цикл for итерация i =  " << i << endl;
        for (int j = 0; j < 5; j++)
        {
            cout << "\tсработал 2-й цикл for итерация j =  " << j << endl;
        }
    }

    return 0;
}
