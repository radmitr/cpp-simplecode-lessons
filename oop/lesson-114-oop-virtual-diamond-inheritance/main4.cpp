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
        HP = 100;
    }

    ~Character()
    {
        cout << "Деструктор Character" << endl;
    }
};

class Orc : public virtual Character  // ← виртуальное наследование!
{
public:
    Orc()
    {
        cout << "Конструктор Orc" << endl;
        HP += 20;  // Орки крепче
    }

    ~Orc()
    {
        cout << "Деструктор Orc" << endl;
    }
};

class Warrior : public virtual Character  // ← виртуальное наследование!
{
public:
    Warrior()
    {
        cout << "Конструктор Warrior" << endl;
        HP += 30;  // Воины выносливее
    }

    ~Warrior()
    {
        cout << "Деструктор Warrior" << endl;
    }
};

// Ромбовидное наследование — OrcWarrior наследуется от Orc и Warrior
class OrcWarrior : public Orc, public Warrior
{
public:
    OrcWarrior()
    {
        cout << "Конструктор OrcWarrior" << endl;
        HP += 10;  // Супер-персонаж
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

    cout << "HP персонажа: " << ow.HP << endl;
    cout << endl;

    return 0;
}
