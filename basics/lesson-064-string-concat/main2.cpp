// C++98 — конкатенация строк.
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    string result;
    string str1 = "Hello";
    string str2 = "World";
    string str3 = "!!!";

    result = str1 + ", " + str2 + str3;

    cout << result << endl;

    return 0;
}
