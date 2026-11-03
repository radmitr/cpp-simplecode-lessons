// C++98 — strlen() и strcat(); C++11 — пустой список инициализации.
#include <cstring>
#include <iostream>

#include "../../common/console.hpp"
using namespace std;

int main()
{
    console::setupConsoleEncoding();
    char result[255]{};
    char str1[255] = "Hello ";
    char str2[255] = "World!";
    //char str1[] = "Hello ";
    //char str2[] = "World!";

    cout << str1 << "\tLEN1 = " << strlen(str1) << endl;   // strlen
    cout << str2 << "\tLEN2 = " << strlen(str2) << endl;

    strcat(result, str1);                                   // strcat
    strcat(result, str2);
    cout << "RESULT1 = " << result << endl;
    return 0;
}
