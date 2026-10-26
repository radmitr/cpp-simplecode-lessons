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
