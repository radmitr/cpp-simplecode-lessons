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
