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
