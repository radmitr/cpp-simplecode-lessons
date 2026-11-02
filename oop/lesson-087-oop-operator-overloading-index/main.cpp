// C++98 — перегрузка operator[] с возвратом ссылки; C++11 — списковая инициализация.
#include <cstddef>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

class TestClass
{
public:
    int& operator[](size_t index)
    {
        return arr[index];
    }

private:
    int arr[5]{5, 44, 4, 987, 69};
};

int main(void)
{
    console::setupConsoleEncoding();

    TestClass a;

    cout << a[1] << endl;
    a[1] = 100;
    cout << a[1] << endl;

    return 0;
}
