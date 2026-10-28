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
    setupConsoleEncoding();

    BracketsMsg m("Привет!");

    Printer p;
    p.print(&m);

    return 0;
}
