// C++98 — класс-обёртка над указателем и деструктор; C++11 — = delete и = default.
#include <iostream>

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

    // При выходе из main() — деструктор вызовется автоматически → delete

    return 0;
}
