// C++98 — перечисления enum.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

enum Speed
{
    MIN = 150,
    RECOMMEND = 600,
    MAX = 800
};

int main(void)
{
    console::setupConsoleEncoding();

    cout << Speed::MIN << endl;
    cout << Speed::RECOMMEND << endl;
    cout << Speed::MAX << endl;

    Speed speed = Speed::MAX;
    cout << speed << endl;

    return 0;
}
