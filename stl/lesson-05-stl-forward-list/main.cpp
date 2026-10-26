#include <iostream>
#include <forward_list>

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
void printForwardList(const std::forward_list<T>& fwdList, const char* separator = "\n")
{
    for (const auto& val : fwdList)
    {
        std::cout << val << separator;
    }
}

int main(void)
{
    setupConsoleEncoding();

    // push_front(..), pop_front()
    std::forward_list<int> fl{5, 1, 33};
    fl.push_front(10);
    fl.push_front(15);
    fl.push_front(15);
    fl.pop_front();
    printForwardList(fl);
    std::cout << std::endl;

    // begin()
    std::forward_list<int>::iterator it = fl.begin();

    // iterator++
    std::cout << *it << std::endl;
    it++;
    std::cout << *it << '\n' << std::endl;
    //it--; // no operator "--" matches these operands

    // insert_after(.., ..)
    fl.insert_after(it, 999);
    printForwardList(fl);
    std::cout << std::endl;

    // erase_after(.., ..)
    fl.erase_after(it);
    printForwardList(fl);
    std::cout << std::endl;

    // before_begin()
    std::forward_list<int>::iterator it2 = fl.before_begin();
    fl.insert_after(it2, 1111);
    printForwardList(fl);
    std::cout << std::endl;

    return 0;
}
