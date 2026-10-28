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
    void takeApple(Apple& apple);
    void eatApple(Apple& apple);
};

class Apple
{
    friend Human;

public:
    inline static int count = 0;

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
    setupConsoleEncoding();

    Apple apple(125, "Red");
    Apple apple2(150, "Green");
    Apple apple3(200, "Yellow");

    // cout << apple.count << endl;
    // cout << apple2.count << endl;
    // cout << apple3.count << endl;

    cout << Apple::count << endl;

    return 0;
}
