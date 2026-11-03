// C++11 — делегирующие конструкторы.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

class Human
{
public:
    Human(string Name)
    {
        this->Name = Name + "!";
        this->Age = 0;
        this->Weight = 0;
        cout << "Создан человек: " << Name << " (возраст: " << Age << ", вес: " << Weight << ")" << endl;
    }

    Human(string Name, int Age) : Human(Name)
    {
        this->Age = Age;
        cout << "Обновлён возраст: " << Age << endl;
    }

    Human(string Name, int Age, int Weight) : Human(Name, Age)
    {
        this->Weight = Weight;
        cout << "Обновлён вес: " << Weight << endl;
    }

    void printInfo() const
    {
        cout << "Имя: " << Name << ", Возраст: " << Age << ", Вес: " << Weight << endl;
    }

private:
    string Name;
    int Age;
    int Weight;
};

int main(void)
{
    console::setupConsoleEncoding();

    Human human("Аристарх");
    human.printInfo();
    cout << endl;

    Human human2("Аристарх", 33);
    human2.printInfo();
    cout << endl;

    Human human3("Аристарх", 41, 65);
    human3.printInfo();
    cout << endl;

    return 0;
}
