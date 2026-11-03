// C++98 — явный вызов метода базового класса; C++11 — override.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

class Msg
{
public:
    Msg(string msg)
    {
        this->msg = msg;
    }

    virtual string getMsg()
    {
        return msg;
    }

private:
    string msg;
};

class BracketsMsg : public Msg
{
public:
    BracketsMsg(string msg) : Msg(msg)
    {
    }

    string getMsg() override
    {
        return "[" + Msg::getMsg() + "]";
    }
};

class Printer
{
public:
    void print(Msg* msg)
    {
        cout << msg->getMsg() << endl;
    }
};

int main(void)
{
    console::setupConsoleEncoding();

    BracketsMsg m("Привет!");

    Printer p;
    p.print(&m);

    return 0;
}
