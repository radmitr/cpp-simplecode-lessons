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

class Weapon
{
public:
    virtual void shoot() = 0;

    void foo()
    {
        cout << "foo()" << endl;
    }
};

class Gun : public Weapon
{
public:
    void shoot() override
    {
        cout << "BANG!" << endl;
    }
};

class SubmachineGun : public Gun
{
public:
    void shoot() override
    {
        cout << "BANG! BANG! BANG!" << endl;
    }
};

class RPG : public Weapon {
public:
    void shoot() override
    {
        cout << "BADABUM!!!" << endl;
    }
};

class Knife : public Weapon {
public:
    void shoot() override
    {
        cout << "VJUH!!!" << endl;
    }
};

class Player {
public:
    void shoot(Weapon* weapon)
    {
        weapon->shoot();
    }
};

int main(void)
{
    setupConsoleEncoding();

    Gun gun;
    gun.shoot(); // → "BANG!"

    SubmachineGun smg;
    smg.shoot(); // → "BANG! BANG! BANG!"

    RPG rpg;
    rpg.shoot(); // → "BADABUM!!!"

    Knife knife;
    knife.shoot(); // → VJUH!!!
    knife.foo();

    Gun* pGun = &smg;
    pGun->shoot();

    Player player;
    player.shoot(&smg);

    return 0;
}
