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

template<typename T>
class SmartPointer
{
public:
    explicit SmartPointer(T* ptr) : ptr(ptr)
    {
        cout << "Constructor" << endl;
    }

    // Конструктор копирования — запрещён (для простоты)
    SmartPointer(const SmartPointer&) = delete;

    // Оператор присваивания — запрещён
    SmartPointer& operator=(const SmartPointer&) = delete;

    ~SmartPointer()
    {
        cout << "Destructor" << endl;
        delete ptr;
    }

    T& operator*()
    {
        return *ptr;
    }

    T* operator->()
    {
        return ptr;
    }

private:
    T* ptr;
};

int main(void)
{
    setupConsoleEncoding();

    SmartPointer<int> sp(new int(5));

    cout << "Значение: " << *sp << endl;
    cout << "Адрес: " << sp.operator->() << endl;

    //SmartPointer<int> sp2 = sp; // cannot be referenced -- it is a deleted function

    return 0;
}
