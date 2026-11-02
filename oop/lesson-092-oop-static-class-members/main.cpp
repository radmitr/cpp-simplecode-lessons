// C++98 — статические поля класса.
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

class Human;
class Apple;

class Human
{
public:
    void takeApple(Apple& apple);
    void eatApple(Apple& apple);
};

class Apple
{
    friend Human;

public:
    static int count;

    Apple(int weight, string color)
    {
        this->weight = weight;
        this->color = color;
        ++count;
    }

    void print()
    {
        cout << "weight: " << weight << ", color: " << color << endl;
    }

private:
    int weight;
    string color;
};

int Apple::count = 0;

void Human::takeApple(Apple &apple)
{
    cout << "takeApple " << "weight: " << apple.weight << ", color: " << apple.color << endl;
}

void Human::eatApple(Apple& apple)
{
    apple.weight = apple.weight - 10;
    cout << "eatApple " << "weight: " << apple.weight << ", color: " << apple.color << endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    Human human;
    Apple apple(125, "red");

    cout << apple.count << endl;

    return 0;
}
