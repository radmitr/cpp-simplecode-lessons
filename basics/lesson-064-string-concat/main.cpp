// C++98 — конкатенация строк; C++11 — списковая инициализация.
#include <cstring>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    char result[255]{};
    char str1[6] = "Hello";
    char str2[255] = "World";

    cout << str1 << endl;
    cout << str2 << endl;

    strcat(result, str1);
    strcat(result, str2);

    cout << result << endl;

    return 0;
}
