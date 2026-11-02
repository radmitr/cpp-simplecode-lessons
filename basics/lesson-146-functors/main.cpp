// C++98 — функторы: перегрузка operator().
#include <cstddef>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

class MyFunctor
{
public:
    void operator()()
    {
        cout << "Я функтор " << count << endl;
        count++;
    }

private:
    int count = 0;
};

int main(void)
{
    console::setupConsoleEncoding();

    MyFunctor f;

    for (size_t i = 0; i < 5; i++)
    {
        f();
    }

    return 0;
}
