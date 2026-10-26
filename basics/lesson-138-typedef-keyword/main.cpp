#include <iostream>
#include <vector>

typedef std::vector<int> int_vector;
typedef std::vector<float> float_vector;

void setupConsoleEncoding()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
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
