// C++98 — дружественные классы.
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
    Apple(int weight, string color)
    {
        this->weight = weight;
        this->color = color;
    }

    void print()
    {
        cout << "weight: " << weight << ", color: " << color << endl;
    }

private:
    int weight;
    string color;
};

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
    apple.print();

    human.takeApple(apple);
    human.eatApple(apple);
    apple.print();

    return 0;
}
