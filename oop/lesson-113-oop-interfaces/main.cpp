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

class Bicycle
{
public:
    virtual ~Bicycle() = default;  // ← виртуальный деструктор, сгенерированный компилятором

    virtual void twistTheWheel() = 0;
    virtual void ride() = 0;
};

class RoadBicycle : public Bicycle
{
public:
    void twistTheWheel() override
    {
        cout << "Поворачиваю руль — еду по асфальту" << endl;
    }

    void ride() override
    {
        cout << "Еду быстро по дороге" << endl;
    }
};

class MountainBicycle : public Bicycle
{
public:
    void twistTheWheel() override
    {
        cout << "Поворачиваю руль — еду по бездорожью" << endl;
    }

    void ride() override
    {
        cout << "Еду по камням и корням" << endl;
    }
};

class Human
{
public:
    void rideOn(Bicycle& bicycle)
    {
        cout << "Человек садится на велосипед..." << endl;
        bicycle.twistTheWheel();
        bicycle.ride();
        cout << "Человек закончил кататься." << endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    RoadBicycle roadBike;
    MountainBicycle mountainBike;

    Human person;

    cout << "=== Езда на дорожном велосипеде ===" << endl;
    person.rideOn(roadBike);

    cout << endl;

    cout << "=== Езда на горном велосипеде ===" << endl;
    person.rideOn(mountainBike);

    return 0;
}
