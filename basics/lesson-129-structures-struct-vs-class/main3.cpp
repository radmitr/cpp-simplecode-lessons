#include <iostream>
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

class MyClass
{
public:
    int a = 5;
};

class MyClass2 : public MyClass
{
};

struct MyStruct
{
    int a = 55;
};

struct MyStruct2 : MyStruct
{
};

int main(void)
{
    setupConsoleEncoding();

    MyClass2 mc2;
    MyStruct2 ms2;

    cout << mc2.a << endl;
    cout << ms2.a << endl;

    return 0;
}
