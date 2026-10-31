#include <iostream>
#include <string>
#include <fstream>

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

class Point
{
public:
    Point() : x(0), y(0), z(0) {}
    Point(int x, int y, int z) : x(x), y(y), z(z) {}

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    int getZ()
    {
        return z;
    }

private:
    int x;
    int y;
    int z;

    friend ostream& operator<<(ostream& os, const Point& p);
    friend istream& operator>>(istream& is, Point& p);
};

ostream& operator<<(ostream& os, const Point& p)
{
    os << p.x << " " << p.y << " " << p.z;
    return os;
}

istream& operator>>(istream& is, Point& p)
{
    is >> p.x >> p.y >> p.z;
    return is;
}

int main(void)
{
    setupConsoleEncoding();

    Point p(487, 212, 946);
    cout << p << endl;

    string path = "myFile.txt";
    fstream fs(path, ios::in | ios::out | ios::app);

    if (!fs.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
    }
    else
    {
        cout << "Файл открыт!" << endl;
        fs << p << endl;
    }

    fs.close();
    return 0;
}
