// C++98 — инкапсуляция и закрытые методы; C++11 — инициализаторы полей внутри класса.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*--------------------------------------------------------------------
 *  инкапсуляция
 *  private методы
 ---------------------------------------------------------------------*/

class CoffeeGrinder
{
private:
    bool voltage = true;

    bool checkVoltage()                 // METHOD (private)
    {
        return this->voltage;
    }

public:
    void SetVoltage(bool vol)           // SET
    {
        this->voltage = vol;
    }

    bool GetVoltage()                   // GET
    {
        return this->voltage;
    }

    void Start()                        // METHOD (public)
    {
        if (checkVoltage())
            cout << "\tVjuHHH! ВжуХХХ! - WORKS!\n" << endl;
        else
            cout << "\tBeep Beep - STOP!\n" << endl;
    }
};

/***********************
          MAIN
************************/
int main()
{
    console::setupConsoleEncoding();

    cout << "\n____________________________________________________________\n" << endl;

    CoffeeGrinder a;
    a.Start();

    a.SetVoltage(false);    // electro off
    a.Start();              // stop

    a.SetVoltage(true);     // electro on
    a.Start();              // works

    return 0;
}
