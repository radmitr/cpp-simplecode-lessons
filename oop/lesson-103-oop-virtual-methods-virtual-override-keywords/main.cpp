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

class Gun
{
public:
    virtual void shoot()
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

class RPG : public Gun {
public:
    void shoot() override
    {
        cout << "BADABUM!!!" << endl;
    }
};

class Player {
public:
    void shoot(Gun* gun)
    {
        gun->shoot();
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

    // Полиморфизм: указатель на базовый класс
    Gun* pGun = &smg;
    pGun->shoot(); // → "BANG! BANG! BANG!"

    Player player;
    player.shoot(&rpg);

    return 0;
}
