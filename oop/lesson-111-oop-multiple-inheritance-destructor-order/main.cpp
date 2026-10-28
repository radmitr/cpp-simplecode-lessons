#include <iostream>
#include <cstdlib>
#include <string>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
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
    setupConsoleEncoding();

    FlyingCar fc;

    cout << endl;

    return 0;
}
