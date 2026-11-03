// C++98 — параметры main(): argc и argv.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*-----------------------------------------------------
* int argc, char* argv[]
* argument count (argc) - кол-во параметров
* argument vector (argv) — массив указателей на C-строки аргументов
------------------------------------------------------*/

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();

    // argv[0] — имя/путь, переданное средой; пользовательские аргументы идут с argv[1].
    for (int i = 0; i < argc; i++)
    {
        cout << "  " << i << "\t" << argv[i] << endl;
    }

    return 0;
}
