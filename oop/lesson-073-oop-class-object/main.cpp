// C++98 — классы, объекты и поля.
#include "../../common/console.hpp"
#include <iostream>
#include <string>

using namespace std;

/*----------------------------------
*   Что такое класс
*   Что такое объект класса
*
*   Класс - новый тип данных
*   пользовательский тип данных
-----------------------------------*/

//-----------------
//   класс Human
//-----------------
class Human
{
public:                             // модификатор доступа
    // поля класса (свойства)
    int age;                        // возраст          )
    int weight;                     // вес
    string name;                    // имя
};

//-----------------
//   класс Point
//-----------------
class Point {
public:
    int x;
    int y;
    int z;
};

int main()
{
    console::setupConsoleEncoding();

    // --------------------------------------------------------------------
    // 1. Объект "firstHuman" класса "Human" (экземпляр) - первый человек
    // --------------------------------------------------------------------
    Human firstHuman;

    // наполнить экземпляр класса значениями (свойства/поля класса)
    firstHuman.age = 30;
    firstHuman.weight = 100;
    firstHuman.name = "Ivanov Ivan Ivanovich";

    // вывод на экран
    cout << firstHuman.age << endl;
    cout << firstHuman.weight << endl;
    cout << firstHuman.name << endl;

    cout << "\n____________________________________________________________\n" << endl;

    // ------------------------------------------
    // 2. Объект "secondHuman" - второй человек
    // ------------------------------------------
    Human secondHuman;

    secondHuman.age = 19;
    secondHuman.weight = 60;
    secondHuman.name = "Noname";

    cout << secondHuman.age << endl;
    cout << secondHuman.weight << endl;
    cout << secondHuman.name << endl;

    cout << "\n____________________________________________________________\n" << endl;

    // -----------------------------------
    //  Экземпляр/объект для класса Point
    // -----------------------------------
    Point a;    // объект "a" класса "Point"

    a.x = 1;    // задать координату x
    a.y = 3;    // задать координату y
    a.z = 5;    // задать координату z

    return 0;
}
