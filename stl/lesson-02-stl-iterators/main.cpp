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

    int arr[] = {2, 8, 9};
    std::cout << arr[1] << std::endl;
    std::cout << *(arr + 1) << std::endl;

    std::vector<int> vector1 = {0, 454, 576, 620, 45, 3};
    std::cout << vector1[1] << std::endl;

    std::vector<int>::iterator it;
    it = vector1.begin();

    *it = 1000;
    std::cout << *it << '\n' << std::endl;

    // iterator
    for (std::vector<int>::iterator it = vector1.begin(); it != vector1.end(); it++)
    {
        *it = *it + 1;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    // const_iterator
    for (std::vector<int>::const_iterator it = vector1.begin(); it != vector1.end(); it++)
    {
        //*it = *it + 1; //expression must be a modifiable lvalue
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    // const_iterator, cbegin(), cend()
    for (std::vector<int>::const_iterator it = vector1.cbegin(); it != vector1.cend(); it++)
    {
        //*it = *it + 1; //expression must be a modifiable lvalue
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    // reverse_iterator, rbegin(), rend()
    for (std::vector<int>::reverse_iterator it = vector1.rbegin(); it != vector1.rend(); it++)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    // advance()
    std::cout << *(it + 3) << std::endl;
    std::advance(it, 3);
    std::cout << *it << '\n' << std::endl;

    // insert()
    std::cout << "------------------------------" << '\n' << std::endl;
    for (std::vector<int>::iterator it = vector1.begin(); it != vector1.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    std::cout << "insert(999)" << '\n' << std::endl;
    std::vector<int>::iterator itInsert = vector1.begin();
    std::advance(itInsert, 5);
    vector1.insert(itInsert, 999);
    for (std::vector<int>::iterator it = vector1.begin(); it != vector1.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    // erase(it)
    std::cout << "erase(it)" << '\n' << std::endl;
    std::vector<int>::iterator itErase = vector1.begin();
    itErase++;
    vector1.erase(itErase);
    for (std::vector<int>::iterator it = vector1.begin(); it != vector1.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    // erase(it, it + 3)
    std::cout << "erase(it, it + 3)" << '\n' << std::endl;
    std::vector<int>::iterator itErase2 = vector1.begin();
    vector1.erase(itErase2, itErase2 + 3);
    for (std::vector<int>::iterator it = vector1.begin(); it != vector1.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}
