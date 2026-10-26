#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdlib>

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
        std::cout << arr[i] << '\t';
    }
    std::cout << std::endl;
}

void push_back(int *&arr, size_t &size, const int value)
{
    int *newArray = new int[size + 1];

    for (size_t i = 0; i < size; i++)
    {
        newArray[i] = arr[i];
    }

    newArray[size] = value;
    size++;

    delete[] arr;
    arr = newArray;
}

int back(const int *arr, size_t size)
{
    if (size < 1)
    {
        throw std::out_of_range("Array is empty");
    }

    return arr[size - 1];
}

void pop_back(int *&arr, size_t &size)
{
    if (size == 0)
    {
        throw std::out_of_range("Cannot pop from empty array");
    }

    size--;
    if (size == 0)
    {
        delete[] arr;
        arr = nullptr;
        return;
    }
    int *newArray = new int[size];

    for (size_t i = 0; i < size; i++)
    {
        newArray[i] = arr[i];
    }

    delete[] arr;
    arr = newArray;
}

void push_front(int *&arr, size_t &size, const int value)
{
    int *newArray = new int[size + 1];

    for (size_t i = 0; i < size; i++)
    {
        newArray[i + 1] = arr[i];
    }

    newArray[0] = value;
    size++;

    delete[] arr;
    arr = newArray;
}

void pop_front(int *&arr, size_t &size)
{
    if (size == 0)
    {
        throw std::out_of_range("Cannot pop from empty array");
    }

    size--;
    if (size == 0)
    {
        delete[] arr;
        arr = nullptr;
        return;
    }
    int *newArray = new int[size];

    for (size_t i = 0; i < size; i++)
    {
        newArray[i] = arr[i + 1];
    }

    delete[] arr;
    arr = newArray;
}

int front(const int *arr, size_t size)
{
    if (size < 1)
    {
        throw std::out_of_range("Array is empty");
    }
    return arr[0];
}

void insert(int *&arr, size_t &size, const int value, const size_t idx)
{
    if (idx > size)
    {
        throw std::out_of_range("Index is out of range");
    }

    int *newArray = new int[size + 1];

    for (size_t i = 0; i < idx; i++)
    {
        newArray[i] = arr[i];
    }

    newArray[idx] = value;

    for (size_t i = idx; i < size; i++)
    {
        newArray[i + 1] = arr[i];
    }

    size++;

    delete[] arr;
    arr = newArray;
}

void erase(int *&arr, size_t &size, const size_t idx)
{
    if (idx >= size)
    {
        throw std::out_of_range("Index is out of range");
    }

    size--;
    if (size == 0)
    {
        delete[] arr;
        arr = nullptr;
        return;
    }
    int *newArray = new int[size];

    for (size_t i = 0; i < idx; i++)
    {
        newArray[i] = arr[i];
    }

    for (size_t i = idx; i < size; i++)
    {
        newArray[i] = arr[i + 1];
    }

    delete[] arr;
    arr = newArray;
}

int at(const int *arr, size_t size, const size_t idx)
{
    if (idx >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return arr[idx];
}

int main(void)
{
    setupConsoleEncoding();

    srand(static_cast<unsigned int>(time(nullptr)));

    size_t size = 5;
    int *arr = new int[size];

    try
    {
        fillArray(arr, size);
        showArray(arr, size);

        push_back(arr, size, 111);
        showArray(arr, size);
        std::cout << "back=" << back(arr, size) << std::endl;

        pop_back(arr, size);
        showArray(arr, size);

        push_front(arr, size, 222);
        showArray(arr, size);
        std::cout << "front=" << front(arr, size) << std::endl;

        pop_front(arr, size);
        showArray(arr, size);

        insert(arr, size, 333, 2);
        showArray(arr, size);
        std::cout << "at(2)=" << at(arr, size, 2) << std::endl;

        erase(arr, size, 2);
        showArray(arr, size);

        insert(arr, size, 333, 1000);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        delete[] arr;
        return 1;
    }

    delete[] arr;
    return 0;
}
