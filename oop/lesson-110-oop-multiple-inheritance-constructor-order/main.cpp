#include <iostream>
#include <cstdlib>
#include <clocale>
#include <string>

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

class Car
{
public:
    string str = "Поле класса машина";

    Car()
    {
        cout << "Вызван конструктор Car" << endl;
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

    void driveAndFly()
    {
        cout << "=== Летающая машина активирована ===" << endl;
        drive();
        fly();
    }
};

int main(void)
{
    setupConsoleEncoding();

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
