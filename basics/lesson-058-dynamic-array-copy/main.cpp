#include <iostream>

using namespace std;

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

void fillArray(int* const arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = rand() % 10;
    }
}

void showArray(const int* const arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i] << '\t';
    }
    cout << endl;
}

int main(void)
{
    setupConsoleEncoding();

    //srand(time(NULL));

    size_t size = 10;
    int* firstArray = new int[size];
    int* secondArray = new int[size];

    fillArray(firstArray, size);
    fillArray(secondArray, size);

    cout << "firstArray:\t";
    showArray(firstArray, size);
    cout << "secondArray:\t";
    showArray(secondArray, size);

    // firstArray = secondArray; // некорректно: копируется ссылка, а не массив

    delete[] firstArray;

    firstArray = new int[size];

    for (size_t i = 0; i < size; i++)
    {
        firstArray[i] = secondArray[i];
    }

    cout << "=========================================================================================" << endl;

    // fillArray(firstArray, size);
    // fillArray(secondArray, size);

    cout << "firstArray:\t";
    showArray(firstArray, size);
    cout << "secondArray:\t";
    showArray(secondArray, size);

    delete[] secondArray;
    delete[] firstArray;

    return 0;
}
