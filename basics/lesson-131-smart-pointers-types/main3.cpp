#include <iostream>
#include <memory>

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

int main(void)
{
    setupConsoleEncoding();

    int* rawPointer = new int(5);

    unique_ptr<int> p1(rawPointer);

    //unique_ptr<int> p2(p1); // cannot be referenced -- it is a deleted function
    unique_ptr<int> p2;
    p2 = move(p1);
    p1.swap(p2);

    int* rawPointer1 = p1.get();
    cout << "Адрес: " << rawPointer1 << endl;
    cout << "Значение: " << *rawPointer1 << endl;

    p1.release();

    unique_ptr<int> p3(rawPointer);
    p3.reset();

    return 0;
}
