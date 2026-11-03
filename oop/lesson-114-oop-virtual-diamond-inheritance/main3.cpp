// C++98 — виртуальное наследование.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

    OrcWarrior ow;

    cout << endl;

    return 0;
}
