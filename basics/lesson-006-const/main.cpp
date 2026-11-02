// C++98 — константы const.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

// Константа - именованная область оперативной памяти с неизменяемыми значениями

int main()
{
    console::setupConsoleEncoding();

    const int COUNT_DAYS_IN_WEEK = 7;
    const char NEW_LINE = '\n';
    const char TAB = '\t';

    cout << NEW_LINE << TAB << COUNT_DAYS_IN_WEEK << NEW_LINE;

    return 0;
}
