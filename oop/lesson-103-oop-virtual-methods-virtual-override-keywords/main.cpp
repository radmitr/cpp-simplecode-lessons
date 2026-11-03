// C++98 — виртуальные методы; C++11 — override.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

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
