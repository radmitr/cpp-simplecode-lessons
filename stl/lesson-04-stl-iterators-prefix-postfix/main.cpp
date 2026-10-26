#include <iostream>
#include <list>

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

template<typename T>
void printList(const std::list<T>& lst)
{
    for (auto it = lst.cbegin(); it != lst.cend(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

int main(void)
{
    setupConsoleEncoding();

    std::list<int>::iterator it;

    ++it;
    it++;

    return 0;
}
