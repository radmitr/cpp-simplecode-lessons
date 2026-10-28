#include <iostream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

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
    setupConsoleEncoding();

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
