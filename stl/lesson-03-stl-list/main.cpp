#include <iostream>
#include <list>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

//using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
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

    std::list<int> list1 = {15, 64, 985};
    printList(list1);
    std::cout << std::endl;

    // push_back(..), push_front(..)
    list1.push_back(5);
    list1.push_front(151);
    printList(list1);
    std::cout << std::endl;

    // begin(), end(), *
    //std::list<int>::iterator it = list1.begin();
    auto it = list1.begin();
    std::cout << *it << '\n' << std::endl;
    for (auto it = list1.begin(); it != list1.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    // printList(..)
    printList(list1);
    std::cout << std::endl;

    // sort()
    list1.sort();
    printList(list1);
    std::cout << std::endl;

    // pop_back(), pop_front()
    list1.pop_back();
    list1.pop_front();
    printList(list1);
    std::cout << std::endl;

    // size()
    std::cout << "size = " << list1.size() << '\n' << std::endl;

    // unique()
    list1.push_back(99);
    list1.push_back(99);
    list1.push_back(99);
    list1.push_front(99);
    list1.push_front(99);
    list1.push_front(99);
    list1.unique();
    printList(list1);
    std::cout << std::endl;

    // reverse()
    list1.reverse();
    printList(list1);
    std::cout << std::endl;

    // insert(.., ..)
    auto it2 = list1.begin();
    list1.insert(it2, 9999);
    printList(list1);
    std::cout << std::endl;

    //it2++;
    list1.insert(it2, 1111);
    printList(list1);
    std::cout << std::endl;

    // advance(.., ..)
    //it2 += 3; //no operator "+=" matches these operands
    std::advance(it2, 3);
    std::cout << *it2 << '\n' << std::endl;

    // erase(..)
    list1.erase(it);
    printList(list1);
    std::cout << std::endl;

    // remove(..)
    list1.remove(99);
    printList(list1);
    std::cout << std::endl;

    // assign(.., ..)
    list1.assign(3, 173745);
    printList(list1);
    std::cout << std::endl;

    std::list<int> list2 = {10, 20, 30};
    list1.assign(list2.begin(), list2.end());
    printList(list1);
    std::cout << std::endl;

    // std::list<int> lst(.., ..)
    std::list<int> list3(3, 55);
    printList(list3);
    std::cout << std::endl;

    // clear()
    list1.clear();
    printList(list1);

    return 0;
}
