#include <iostream>
#include <memory>

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
