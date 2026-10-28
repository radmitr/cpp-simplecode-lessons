#include <iostream>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

typedef std::vector<int> int_vector;
typedef std::vector<float> float_vector;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

int main(void)
{
    setupConsoleEncoding();

    std::vector<int> vector1;
    int_vector vector2;
    float_vector vector3;

    for (size_t i = 0; i < 10; i++) // typedef unsigned __int64 size_t;
    {
        /* code */
    }

    return 0;
}
