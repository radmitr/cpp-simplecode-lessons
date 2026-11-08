// C++98 — вложенные объекты, ссылки и время жизни.
#include <iostream>
#include <string>

struct Cap
{
    std::string color;
};

struct Owner
{
    Cap cap{"green"}; // Собственный объект: композиция.
};

struct Borrower
{
    Cap& cap; // Ссылка на внешний объект: агрегация, владение не передаётся.
};

int main()
{
    Owner owner;
    Cap external{"red"};
    {
        Borrower person{external};
        person.cap.color = "blue";
        std::cout << "Borrowed cap: " << person.cap.color << '\n';
    } // person уничтожен; external продолжает существовать.
    std::cout << "External cap after borrower: " << external.color << '\n';
    std::cout << "Owned cap: " << owner.cap.color << '\n';
    // external должен жить дольше всех использующих его Borrower.
    return external.color == "blue" && owner.cap.color == "green" ? 0 : 1;
}
