// C++98 — rand(), srand() и time().
#include <cstdlib>
#include <cstddef>
#include <iostream>
#include <ctime>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    srand(time(NULL));

    const int SIZE = 10;

    int arr[SIZE];

    for (size_t i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 100;
    }

    for (size_t i = 0; i < SIZE; i++)
    {
        cout << arr[i] << endl;
    }

    return 0;
}
