// C++98 — методы класса.
#include "../../common/console.hpp"
#include <iostream>
#include <string>

using namespace std;

/*---------------------
*   методы класса
*   функции класса
----------------------*/
class Human                         // класс Human
{
public:                             // модификатор доступа
    int age;                        // Поля конкретного объекта Human.
    int weight;
    string name;

    void Print()                    // метод Print
    {
        cout << "\n Имя: " << name << "\n Вес: " << weight << "\n Возраст: " << age << endl;
    }
};

/***********************
          MAIN
************************/
int main()
{
    console::setupConsoleEncoding();

    cout << "\n____________________________________________________________\n" << endl;

    // Объект(экземпляр) - первый человек
    Human firstHuman;
    firstHuman.age = 30;
    firstHuman.name = "Иванов Иван";
    firstHuman.weight = 100;
    firstHuman.Print();                      // вызов общего метода "Print" для первого объекта

    // Объект(экземпляр) - второй человек
    Human secondHuman;
    secondHuman.age = 19;
    secondHuman.name = "Петр Петров";
    secondHuman.weight = 60;
    secondHuman.Print();                    // вызов общего метода "Print" для второго объекта

    return 0;
}
