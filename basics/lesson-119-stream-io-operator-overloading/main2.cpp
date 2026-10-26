#include <iostream>
#include <string>
#include <fstream>

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

class Point
{
    friend ostream& operator<<(ostream& os, const Point& p);
    friend istream& operator>>(istream& is, Point& p);

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

        Point p2;
        cout << "Введите координаты:" << endl;
        cin >> p2;

        cout << p2 << endl << endl;
        fs << p2 << endl;

        fs.seekg(0);
        while(true)
        {
            Point p3;
            fs >> p3;

            if (fs.eof())
            {
                break;
            }
            cout << p3 << endl;
        }
    }


    fs.close();
    return 0;
}
