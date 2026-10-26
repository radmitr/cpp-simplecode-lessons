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
        ++count;
        id = count;
    }

    int getId()
    {
        return id;
    }

    static int getCount()
    {
        return count;
    }

    static void changeColor(Apple& apple, string color)
    {
        apple.color = color;
    }

    void changeColorNonStatic(string color)
    {
        this->color = color;
    }

    void print()
    {
        cout << "Apple weight: " << weight << ", color: " << color;
    }

    void println()
    {
        cout << "Apple weight: " << weight << ", color: " << color << endl;
    }

private:
    inline static int count = 0;
    int id;
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

    cout << apple.getId() << endl;
    cout << apple2.getId() << endl;
    cout << apple3.getId() << endl;

    cout << Apple::getCount() << endl;

    Apple::changeColor(apple, "Black");
    apple.println();

    apple.changeColorNonStatic("Yellow-Red");
    apple.println();

    return 0;
}
