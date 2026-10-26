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
