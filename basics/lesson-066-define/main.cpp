// C++98 — объектоподобные макросы #define.
#include <iostream>

#include "../../common/console.hpp"

#define PI 3.14
#define tab "\t"

/*
#define begin {
#define end }
*/

using namespace std;

/*
    Препроцессор
    #define
*/

int main()
{
    console::setupConsoleEncoding();

    cout << PI << endl;
    cout << "text\ttext (code)" << endl;
    cout << "text" << tab << "text (tab)" << endl;

    /*
    for (int i = 0; i < 5; i++)
    begin
        cout << i << endl;
    end
    */

    return 0;
}
