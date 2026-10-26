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
public:
    int x;
    int y;
    int z;

    Point() : x(0), y(0), z(0)
    {
    }

    Point(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void print() const
    {
        cout << "Point(" << x << ", " << y << ", " << z << ")" << endl;
    }

    // friend ostream& operator<<(ostream& os, const Point& p)
    // {
    //     os << p.x << " " << p.y << " " << p.z;
    //     return os;
    // }

    // friend istream& operator>>(istream& is, Point& p)
    // {
    //     is >> p.x >> p.y >> p.z;
    //     return is;
    // }
};

int main(void)
{
    setupConsoleEncoding();

    Point p1(487, 212, 946);
    cout << "Исходный объект: ";
    p1.print();

    ofstream fout("point.dat", ios::binary | ios::app);
    if (!fout.is_open())
    {
        cerr << "Ошибка открытия файла для записи" << endl;
        return 1;
    }

    fout.write(reinterpret_cast<char*>(&p1), sizeof(Point));
    fout.close();
    cout << "Объект записан в файл point.dat" << endl;

    Point p2;
    ifstream fin("point.dat", ios::binary);
    if (!fin.is_open())
    {
        cerr << "Ошибка открытия файла для чтения" << endl;
        return 1;
    }

    while (fin.read(reinterpret_cast<char*>(&p2), sizeof(Point)))
    {
        cout << "Прочитанный объект: ";
        p2.print();
    }

    fin.close();

    return 0;
}
