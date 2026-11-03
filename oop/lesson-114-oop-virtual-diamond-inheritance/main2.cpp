// C++98 — виртуальное наследование.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

class Component
{
public:
    string companyName;

    Component(string companyName)
    {
        cout << "Конструктор Component" << endl;
        this->companyName = companyName;
    }

    ~Component()
    {
        cout << "Деструктор Component" << endl;
    }
};

class GPU : public virtual Component  // ← виртуальное наследование!
{
public:
    GPU(string companyName) : Component(companyName)
    {
        cout << "Конструктор GPU" << endl;
    }

    ~GPU()
    {
        cout << "Деструктор GPU" << endl;
    }
};

class Memory : public virtual Component  // ← виртуальное наследование!
{
public:
    Memory(string companyName) : Component(companyName)
    {
        cout << "Конструктор Memory" << endl;
    }

    ~Memory()
    {
        cout << "Деструктор Memory" << endl;
    }
};

// Ромбовидное наследование — GraphicCard наследуется от GPU и Memory
class GraphicCard : public GPU, public Memory
{
public:
    GraphicCard(string GPUCompanyName, string MemoryCompanyName)
        : Component(GPUCompanyName)  // ← Инициализируем базовый класс напрямую
        , GPU(GPUCompanyName)
        , Memory(MemoryCompanyName)
    {
        cout << "Конструктор GraphicCard" << endl;
    }

    ~GraphicCard()
    {
        cout << "Деструктор GraphicCard" << endl;
    }
};

int main(void)
{
    console::setupConsoleEncoding();

    GraphicCard gc("AMD", "Samsung");
    cout << endl;

    cout << "Имя компании GPU: " << gc.GPU::companyName << endl;
    cout << "Имя компании Memory: " << gc.Memory::companyName << endl;
    cout << endl;

    return 0;
}
