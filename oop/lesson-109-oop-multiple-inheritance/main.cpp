// C++98 — множественное наследование.
#include <iostream>
#include <cstdlib>
#include <string>

#include "../../common/console.hpp"

using namespace std;

class Car
{
public:
    string str = "Поле класса машина";

    void drive()
    {
        cout << "Я еду!" << endl;
    }
};

class Airplane
{
public:
    string str2 = "Поле класса самолёта";

    void fly()
    {
        cout << "Я лечу!" << endl;
    }
};

class FlyingCar : public Car, public Airplane
{
public:
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

    fc.drive();
    fc.fly();
    cout << endl;

    fc.driveAndFly();
    cout << endl;

    cout << fc.str << endl;
    cout << fc.str2 << endl;

    Car* ptrC = &fc;

    Airplane* ptrA = &fc;

    return 0;
}
