#include <iostream>

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

//template<typename T>
template<class T>
class MyClass
{
public:
    MyClass(T value)
    {
        this->value = value;
    }

    void dataTypeSize()
    {
        cout << sizeof(T) << endl;
    }

    T getValue()
    {
        return value;
    }

private:
    T value;
};

class Point
{
public:
    int x;
    int y;
    int z;

    Point() : x(0), y(0), z(0) {}

    Point(int x, int y, int z) : x(x), y(y), z(z) {}
};

int main(void)
{
    setupConsoleEncoding();

    int a = 5;
    MyClass<int> myclass(a);
    myclass.dataTypeSize();

    double b = 5.3847538;
    MyClass<double> myclass2(b);
    myclass2.dataTypeSize();

    Point point;
    MyClass<Point> myclass3(point);
    myclass3.dataTypeSize();

    int a1 = myclass.getValue();
    cout << a1 << endl;

    return 0;
}
