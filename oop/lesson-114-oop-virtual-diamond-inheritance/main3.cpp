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

class Character
{
public:
    int HP;

    Character()
    {
        cout << "Конструктор Character" << endl;
    }

    ~Character()
    {
        cout << "Деструктор Character" << endl;
    }
};

class Orc : public Character
{
public:
    Orc()
    {
        cout << "Конструктор Orc" << endl;
    }

    ~Orc()
    {
        cout << "Деструктор Orc" << endl;
    }
};

class Warrior : public Character
{
public:
    Warrior()
    {
        cout << "Конструктор Warrior" << endl;
    }

    ~Warrior()
    {
        cout << "Деструктор Warrior" << endl;
    }
};

class OrcWarrior : public Orc, public Warrior
{
public:
    OrcWarrior()
    {
        cout << "Конструктор OrcWarrior" << endl;
    }

    ~OrcWarrior()
    {
        cout << "Деструктор OrcWarrior" << endl;
    }
};


int main(void)
{
    setupConsoleEncoding();

    OrcWarrior ow;

    cout << endl;

    return 0;
}
