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
