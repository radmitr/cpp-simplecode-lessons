// C++98 — символьные массивы и строки с завершающим нулём.
#include "../../common/console.hpp"
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
    console::setupConsoleEncoding();
    char str1[255] = "Hello ";
    char str2[255] = "World!";

    cout << str1 << "\tLEN1 = " << strlen(str1) << endl;   // strlen
    cout << str2 << "\tLEN2 = " << strlen(str2) << endl;
    return 0;
}
