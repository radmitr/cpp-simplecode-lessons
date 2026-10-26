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
