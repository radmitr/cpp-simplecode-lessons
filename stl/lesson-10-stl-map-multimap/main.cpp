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

    // std::pair<.., ..>
    std::pair<const int, std::string> p(1, "телефон");
    std::cout << p.first << std::endl;
    std::cout << p.second << std::endl;

    //---------------------------------------------------------------

    // std::map<.., ..>
    std::map<int, std::string> map1;

    // insert()
    auto result = map1.insert(p); // std::pair<std::map<int, std::string>::iterator, bool>
    result = map1.insert(std::make_pair(2, "ноутбук"));
    result = map1.insert(std::pair<int, std::string>(3, "фотоаппарат"));
    result = map1.insert({4, "планшет"});
    printContainer(map1);
    std::cout << std::endl;

    // emplace()
    result = map1.emplace(5, "монитор");
    result = map1.emplace(6, "клавиатура");
    result = map1.emplace(22, "гаджет");
    std::cout << "Успешно вставлено: " << result.second << std::endl;
    result = map1.emplace(22, "гавлвовлоджет");
    std::cout << "Успешно вставлено: " << result.second << std::endl;
    result = map1.emplace(22, "влопвлопв");
    printContainer(map1);
    std::cout << std::endl;

    // find()
    auto it = map1.find(22);
    if (it != map1.end())
    {
        std::cout << *it << std::endl;
        std::cout << it->first << std::endl;
        std::cout << it->second << std::endl;
    }
    else
    {
        std::cout << "элемент не найден" << std::endl;
    }

    it = map1.find(222);
    std::cout << (it == map1.end()) << std::endl;
    std::cout << std::endl;

    // [..]
    std::cout << map1[1] << std::endl;
    std::cout << map1[2] << std::endl;
    std::cout << map1[3] << std::endl;
    std::cout << map1[999] << std::endl;
    std::cout << map1[4] << std::endl;
    std::cout << map1[5] << std::endl;
    std::cout << std::endl;

    // erase()
    map1.erase(22);
    printContainer(map1);
    std::cout << std::endl;

    //---------------------------------------------------------------

    std::map<std::string, int> map2;

    map2.emplace("Петя", 3445);
    map2.emplace("Маша", 6431);
    map2.emplace("Миша", 2973);
    printContainer(map2);
    std::cout << std::endl;

    map2["Петя"] = 99;

    std::cout << map2["Петя"] << std::endl;
    std::cout << map2["Маша"] << std::endl;
    std::cout << map2["Миша"] << std::endl;
    std::cout << std::endl;

    map2["Вася"] = 9794;
    printContainer(map2);
    std::cout << std::endl;

    map2.at("Вася") = 3;
    printContainer(map2);
    std::cout << std::endl;

    try
    {
        map2.at("Билли") = 333;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n' << std::endl;
    }

    map2.erase("Вася");
    printContainer(map2);
    std::cout << std::endl;

    return 0;
}
