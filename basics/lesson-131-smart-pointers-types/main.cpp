// C++98 — обёртка над указателем; C++11 — запрет копирования через = delete.
#include <iostream>
#include <memory>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

    SmartPointer<int> sp(new int(5));

    cout << "Значение: " << *sp << endl;
    cout << "Адрес: " << sp.operator->() << endl;

    //SmartPointer<int> sp2 = sp; // cannot be referenced -- it is a deleted function

    return 0;
}
