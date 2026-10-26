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

class GPU : public Component
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

class Memory : public Component
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

class GraphicCard : public GPU, public Memory
{
public:
    GraphicCard(string GPUCompanyName, string MemoryCompanyName)
        : GPU(GPUCompanyName), Memory(MemoryCompanyName)
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
    setupConsoleEncoding();

    GraphicCard gc("AMD", "Samsung");

    cout << endl;

    cout << "Имя компании GPU: " << gc.GPU::companyName << endl;
    cout << "Имя компании Memory: " << gc.Memory::companyName << endl;

    cout << endl;

    return 0;
}
