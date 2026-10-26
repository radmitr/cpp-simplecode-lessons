#include <iostream>
#include <vector>

//using namespace std;

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

    std::vector<int> vector1 = {11, 46, 9};

    std::vector<int>::iterator it = vector1.begin();

    auto it2 = vector1.begin();

    for (std::vector<int>::iterator it = vector1.begin(); it != vector1.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    for (auto it = vector1.begin(); it != vector1.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}
