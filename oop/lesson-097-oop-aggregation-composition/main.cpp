// C++98 — вложенные объекты и указатели на другие объекты.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

class Cap {
public:
    string getColor()
    {
        return color;
    }

private:
    string color = "red";
};

class Model
{
public:
    void inspectModel()
    {
        cout << "Кепка " << cap.getColor() << " цвета." << endl;
    }

private:
    Cap cap;
};

class Human
{
public:
    void Think()
    {
        brain.Think();
    }

    void inspectTheCap()
    {
        cout << "Моя кепка " << cap.getColor() << " цвета." << endl;
    }

private:
    class Brain
    {
    public:
        void Think()
        {
            cout << "Я думаю!" << endl;
        }
    };

    Brain brain;
    Cap cap;
};

int main(void)
{
    console::setupConsoleEncoding();

    Human human;
    human.Think();
    human.inspectTheCap();

    Model model;
    model.inspectModel();

    return 0;
}
