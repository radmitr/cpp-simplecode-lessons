#include <iostream>

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

class MyClass
{
public:
    int a = 11;

    void msg()
    {
        cout << "msg" << endl;
    }

    void lambda()
    {
        auto f = [this]() {
            this->msg();
        };
        f();
    }
};

int main(void)
{
    setupConsoleEncoding();

    MyClass m;

    m.lambda();

    return 0;
}
