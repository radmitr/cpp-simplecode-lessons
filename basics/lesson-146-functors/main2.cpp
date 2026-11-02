// C++98 — функторы: перегрузка operator().
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

class MyFunctor
{
public:
    int operator()(int a, int b)
    {
        cout << "Я функтор " << endl;
        return a + b;
    }

private:
    int count = 0;
};

int main(void)
{
    console::setupConsoleEncoding();

    MyFunctor f;

    int result = f(3, 2);

    cout << result << endl;

    return 0;
}
