// C++98 — разрешение неоднозначности при множественном наследовании.
#include <cstdlib>
#include <iostream>
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

    void use()
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

    void use()
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
        //use(); // "FlyingCar::use" is ambiguous !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
};

int main(void)
{
    console::setupConsoleEncoding();

    FlyingCar fc;

    ((Car)fc).use(); // Создаётся временный объект типа Car, копируя подобъект Car из fc
    ((Airplane)fc).use(); // Создаётся временный объект типа Airplane, копируя подобъект Airplane из fc

    cout << endl;

    fc.Car::use();
    fc.Airplane::use();

    cout << endl;
    return 0;
}
