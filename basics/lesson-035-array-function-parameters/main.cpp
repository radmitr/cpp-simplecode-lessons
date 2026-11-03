// C++98 — параметры-массивы и явная передача размера.
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/* Передача массива в функцию */

// --- FillArray ---
void FillArray(int arr[], const int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10;    // random numbers: 0...9
    }
}

// --- PrintArray ---
void PrintArray(int arr[], const int size)
{
    for (int i = 0; i < size; i++)
    {
        printf(" index: [%i]\t random-number: %i\n", i, arr[i]);
    }
}

// === main ====
int main()
{
    console::setupConsoleEncoding();

    const int SIZE = 10;
    int massiv[SIZE];

    FillArray(massiv, SIZE);    // заполнить массив
    PrintArray(massiv, SIZE);   // вывести массив
}
