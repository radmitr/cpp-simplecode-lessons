#include <iostream>

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

class PC
{
public:
    PC() : state(PCState::OFF)
    {
    }

    //enum class PCState // scoped enum
    enum PCState // unscoped enum
    {
        OFF,
        ON,
        SLEEP,
    };

    PCState getState() const
    {
        return state;
    }

    void setState(PCState state)
    {
        this->state = state;
    }

private:
    PCState state;
};

int main(void)
{
    setupConsoleEncoding();

    PC pc;

    cout << pc.getState() << endl;
    pc.setState(PC::PCState::ON);
    cout << pc.getState() << endl << endl;

    cout << "OFF: " << PC::PCState::OFF << endl;
    cout << "ON: " << PC::PCState::ON << endl;
    cout << "SLEEP: " << PC::PCState::SLEEP << endl << endl;

    switch (pc.getState())
    {
    case PC::PCState::OFF:
        cout << "ПК выключен" << endl;
        break;
    case PC::PCState::ON:
        cout << "ПК включен" << endl;
        break;
    case PC::PCState::SLEEP:
        cout << "ПК в спящем режиме" << endl;
        break;
    default:
        break;
    }

    return 0;
}
