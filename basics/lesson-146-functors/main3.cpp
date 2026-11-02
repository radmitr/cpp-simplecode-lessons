// C++98 — функторы: перегрузка operator(); C++11 — auto.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

class EvenFunctor
{
public:
    void operator()(int value)
    {
        if (value % 2 == 0)
        {
            evenSum += value;
            ++evenCount;
        }
    }

    void showEvenSum()
    {
        cout << "Сумма чётных чисел: " << evenSum << endl;
    }

    void showEvenCount()
    {
        cout << "Количество чётных чисел: " << evenCount << endl;
    }

private:
    int evenSum = 0;
    int evenCount = 0;
};

int main(void)
{
    console::setupConsoleEncoding();

    int arr[] = {23, 76, 2, 65, 22, 1, 9, 92, 34};

    EvenFunctor ef;

    for (auto element : arr)
    {
        ef(element);
    }

    ef.showEvenSum();
    ef.showEvenCount();

    return 0;
}
