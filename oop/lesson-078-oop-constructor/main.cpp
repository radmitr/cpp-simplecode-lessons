// C++98 — конструкторы с параметрами и по умолчанию.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*---------------------------
*   конструктор класса
*   с параметрами
*   конструктор по умолчанию
----------------------------*/

// Класс - это шаблон по которому создаётся объект

// --- POINT ---
class Point {
private:            // Закрытые поля объекта
    int x;
    int y;

public:

    // Конструктор по умолчанию
    Point()
    {
    }

    // --- Constructor ---
    // Конструктор вызывается сам, когда создаётся объект класса
    // (вызывается при создании объекта; возвращаемый тип не указывается)
    Point(int x, int y) // перегрузка конструктора
    {
        this->x = x;
        this->y = y;
    }

    // --- Getters-Setters ---
    int GetX()              // GET X
    {
        return this->x;
    }
    int GetY()              // GET Y
    {
        return this->y;
    }
    void SetX(int x)        // SET X
    {
        this->x = x;
    }
    void SetY(int y)        // SET Y
    {
        this->y = y;
    }

    // --- Method ---
    void Print()            // публичный метод
    {
        cout << " X = " << x << "\t Y =  " << y << endl << endl;
    }
};

/***********************
      === MAIN ===
************************/
int main()
{
    console::setupConsoleEncoding();

    cout << "\n____________________________________________________________\n" << endl;

    // инициализация через "CONSTRUCTOR" (с перегрузкой)
    Point a(5, 44);
    a.Print();

    Point b(77, 9);
    b.Print();

    Point c(10, 20);
    c.Print();

    // инициализация через "SETTERS-GETTERS"
    Point d;        // без параметров конструктора (по умолчанию)
    d.SetX(111);
    d.SetY(222);
    d.Print();

    return 0;
}
