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

class A
{
public:
    string msgOne = "Сообщение один";

private:
    string msgTwo = "Сообщение два";

protected:
    string msgThree = "Сообщение три";
};

class B : private A
{
public:
    void printMsg()
    {
        cout << msgOne << endl;   // ✅ OK — public в базе → public в наследнике
        // cout << msgTwo << endl; // ❌ ОШИБКА — private в базе → недоступно
        cout << msgThree << endl; // ✅ OK — protected в базе → protected в наследнике
    }
};

int main(void)
{
    setupConsoleEncoding();

    B b;
    b.printMsg();

    // Попробуем обратиться к полям напрямую (извне)
    // cout << b.msgOne << endl;   // ✅ OK — public
    // cout << b.msgTwo << endl;   // ❌ ОШИБКА — private
    // cout << b.msgThree << endl; // ❌ ОШИБКА — protected

    return 0;
}
