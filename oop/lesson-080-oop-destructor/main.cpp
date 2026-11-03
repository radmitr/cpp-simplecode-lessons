// C++98 — деструкторы и освобождение ресурсов.
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

/*----------------
*   деструктор
*----------------*/

class MyClass
{
private:
    int* data;                              // указатель на дин. массив

public:

    // Constructor
    MyClass(int size)
    {
        data = new int[size];               // динамический массив

        for (int i = 0; i < size; i++)      // заполнить дин. массив
        {
            this->data[i] = i;
        }
        cout << " Объект: " << this->data << "\n Вызвался конструктор\n" << endl;
        for (int i = 0; i < size; i++)      // вывести дин. массив
        {
            cout << this->data[i] << " ";
        }
        cout << endl;
    }

    // Деструктор автоматически вызывается при выходе объекта из области видимости.
    ~MyClass()
    {
        cout << " Объект: " << this->data << "\n Вызвался деструктор" << endl;
        delete[] this->data; // Освобождаем массив после вывода его адреса.
    }
};

void Foo()
{
    cout << "\n --- НАЧАЛО ВЫПОЛНЕНИЯ --- \n" << endl;
    MyClass a(10); // для size = 10
    cout << "\n --- КОНЕЦ ВЫПОЛНЕНИЯ --- \n" << endl;
}

/***********************
      === MAIN ===
************************/
int main()
{
    console::setupConsoleEncoding();

    cout << "\n____________________________________________________________\n" << endl;

    //MyClass a(1);             // Создание объекта соотв. класса
    //MyClass b(2);
    //MyClass c(3);

    Foo();  // test

    return 0;
}
