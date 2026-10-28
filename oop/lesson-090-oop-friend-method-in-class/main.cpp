#include <iostream>
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

class Human;
class Apple;

class Human
{
public:
    // void takeApple(Apple& apple)
    // {
    //     cout << "takeApple " << "weight: " << apple.weight << ", color: " << apple.color << endl;
    // }
    void takeApple(Apple& apple);

    void eatApple(Apple& apple)
    {
    }
};

class Apple
{
public:
    Apple(float weight, string color)
    {
        this->weight = weight;
        this->color = color;
    }

private:
    float weight;
    string color;

    friend void Human::takeApple(Apple& apple);
};

int main(void)
{
    setupConsoleEncoding();

    Human human;
    Apple apple(125.3, "red");

    human.takeApple(apple);

    return 0;
}

void Human::takeApple(Apple &apple)
{
    cout << "takeApple " << "weight: " << apple.weight << ", color: " << apple.color << endl;
}
