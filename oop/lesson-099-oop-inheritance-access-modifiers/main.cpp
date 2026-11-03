// C++98 — спецификаторы доступа при наследовании.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

    B b;
    b.printMsg();

    // Попробуем обратиться к полям напрямую (извне)
    // cout << b.msgOne << endl;   // ✅ OK — public
    // cout << b.msgTwo << endl;   // ❌ ОШИБКА — private
    // cout << b.msgThree << endl; // ❌ ОШИБКА — protected

    return 0;
}
