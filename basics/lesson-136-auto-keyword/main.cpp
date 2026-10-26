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

int main(void)
{
    setupConsoleEncoding();

    auto a = 10;
    auto b = 1.44;
    auto c = "string";
    auto d = true;
    //auto e; // cannot deduce 'auto' type (initializer required)

    cout << "a = " << a << ", sizeof(a) = " << sizeof(a) << endl;
    cout << "b = " << b << ", sizeof(b) = " << sizeof(b) << endl;
    cout << "c = " << c << ", sizeof(c) = " << sizeof(c) << endl;
    cout << "d = " << d << ", sizeof(d) = " << sizeof(d) << endl;

    return 0;
}
