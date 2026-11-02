// C++98 — порядок деструкторов при множественном наследовании.
#include <iostream>
#include <cstdlib>
#include <string>

#include "../../common/console.hpp"

using namespace std;

class Car
{
public:
    string str = "Поле класса машина";

    Car()
    {
        cout << "Вызван конструктор Car" << endl;
    }

    ~Car()
    {
        cout << "Вызван деструктор Car" << endl;
    }

    void drive()
    {
        cout << "Я еду!" << endl;
    }
};

class Airplane
{
public:
    string str2 = "Поле класса самолёта";

    Airplane()
    {
        cout << "Вызван конструктор Airplane" << endl;
    }

    ~Airplane()
    {
        cout << "Вызван деструктор Airplane" << endl;
    }

    void fly()
    {
        cout << "Я лечу!" << endl;
    }
};

class FlyingCar : public Car, public Airplane
{
public:
    FlyingCar()
    {
        cout << "Вызван конструктор FlyingCar" << endl;
    }

    ~FlyingCar()
    {
        cout << "Вызван деструктор FlyingCar" << endl;
    }

    void driveAndFly()
    {
        cout << "=== Летающая машина активирована ===" << endl;
        drive();
        fly();
    }
};

int main(void)
{
    console::setupConsoleEncoding();

    FlyingCar fc;

    cout << endl;

    return 0;
}
