// C++98 — указатель this.
#include "../../common/console.hpp"
#include <iostream>
#include <string>

using namespace std;

/*-------------------------
 * Ключевое слово this
 *------------------------*/

 // --- CLASS POINT ---

class Point {
private:            // Закрытые поля объекта
    int x;
    int y;

public:

    // Конструктор по умолчанию
    Point() : x(0), y(0)
    {
        cout << this << " constructor 1" << endl;
    }

    // --- Constructor ---
    // Конструктор вызывается сам, когда создаётся объект класса
    // (вызывается при создании объекта; возвращаемый тип не указывается)
    Point(int x, int y) // перегрузка конструктора
    {
        this->x = x;
        this->y = y;
        cout << this << " constructor 2" << endl;   // this - указатель (адрес) для каждого объекта класса
    }

    // --- Getters-Setters ---
    int GetX()          // GET X
    {
        return this->x;
    }
    int GetY()          // GET Y
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

    Point p1;
    Point p2(11, 22);

    cout << "\n____________________________________________________________\n" << endl;

    return 0;
}
