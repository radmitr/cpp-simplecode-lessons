// C++98 — std::cout и функции вывода из <cstdio>.
#include <clocale>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common/console.hpp"

using namespace std;

int main()
{
    console::setupConsoleEncoding();

    cout << "\n \"HELLO WORLD!\" \n";               // <iostream>
    cout << endl << " Hello World!" << endl;
    printf(" HALLO WELT!\n");
    puts(" ПРИВЕТ МИР!");
    fprintf(stderr, " ПРИВЕТ МИР!\n");

    return 0;
}
