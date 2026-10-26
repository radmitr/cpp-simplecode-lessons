#include <iostream>
#include <map>
#include <string>

// using namespace std;

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

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename Container>
void printContainer(
    const Container &container,
    const char *separator = "\n",
    std::ostream &os = std::cout)
{
    auto it = std::begin(container);
    if (it != std::end(container))
    {
        os << *it;
        ++it;
        for (; it != std::end(container); ++it)
        {
            os << separator << *it;
        }
    }
    os << std::endl;
}

int main(void)
{
    setupConsoleEncoding();

    std::multimap<std::string, int> map1;

    map1.emplace("Петя", 3445);
    map1.emplace("Петя", 100);
    map1.emplace("Маша", 6431);
    map1.emplace("Миша", 2973);
    printContainer(map1);

    //map1["Петя"]; // no operator "[]" matches these operands
    //map1.at("Петя"); // class std::multimap has no member "at"

    return 0;
}
