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
