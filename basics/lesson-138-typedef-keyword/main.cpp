// C++98 — псевдонимы типов typedef.
#include <cstddef>
#include <iostream>
#include <vector>

#include "../../common/console.hpp"

typedef std::vector<int> int_vector;
typedef std::vector<float> float_vector;

int main(void)
{
    console::setupConsoleEncoding();

    std::vector<int> vector1;
    int_vector vector2;
    float_vector vector3;

    for (size_t i = 0; i < 10; i++) // typedef unsigned __int64 size_t;
    {
        /* code */
    }

    return 0;
}
