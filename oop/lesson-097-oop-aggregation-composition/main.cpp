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
    setupConsoleEncoding();

    Human human;
    human.Think();
    human.inspectTheCap();

    Model model;
    model.inspectModel();

    return 0;
}
