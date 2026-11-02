// C++98 — условная компиляция: #if, #ifdef и #ifndef.
#include "../../common/console.hpp"
#include <iostream>

#define DEBUG 5

using namespace std;

/*---------------------------------------------------------------------
 *  Условная компиляция:
 *  Директивы условной компиляции:
 *  #ifdef #else #endif #if #elif #endif #ifndef
 ---------------------------------------------------------------------*/

int main()
{
    console::setupConsoleEncoding();

#if DEBUG
    cout << "\n --> Начало цикла" << endl;
#endif // DEBUG

    for (int i = 0; i < 4; i++)
    {
        cout << "\t" << i << endl;
    }

#ifdef DEBUG
    cout << " <-- Конец цикла\n" << endl;
#endif

#ifdef DEBUG
    cout << "\nДебаг определен\n" << endl;
#else
    cout << "\nДебаг НЕ определен\n" << endl;
#endif

#ifndef DEBUG
    cout << "\n-- DEBUG OFF --\n" << endl;
#else
    cout << "\n-- DEBUG ON --\n" << endl;
#endif

#if DEBUG > 4
    cout << "\n-- DEBUG > 4 --\n" << endl;
#else
    cout << "\n-- DEBUG <= 4 --\n" << endl;
#endif

#if DEBUG < 4
    cout << "\n-- DEBUG < 4 --\n" << endl;
#elif DEBUG == 5
    cout << "\n-- DEBUG == 5 --\n" << endl;
#endif

    return 0;
}
