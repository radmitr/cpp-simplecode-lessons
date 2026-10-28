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

class Pixel
{
public:
    Pixel()
    {
        r = g = b = 0;
    }

    Pixel(int r, int g, int b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    string getInfo()
    {
        return "Pixel: r=" + to_string(r) + ", g=" + to_string(g) + ", b=" + to_string(b);
    }

private:
    int r;
    int g;
    int b;
};

int main(void)
{
    setupConsoleEncoding();

    // static array
    const int LENGTH = 5;

    Pixel arr[LENGTH];
    arr[0] = Pixel(111, 11, 17);
    cout << arr[0].getInfo() << endl;

    // Pixel pixels[LENGTH] {
    //     Pixel(0, 4, 64),
    //     Pixel(11, 50, 155),
    //     Pixel(100, 215, 71),
    //     Pixel(1, 254, 125),
    //     Pixel(201, 83, 253)
    // };

    // dynamic array
    int LENGTH2 = 5;

    Pixel* arr2 = new Pixel[LENGTH2];
    arr2[0] = Pixel(222, 22, 27);
    cout << arr2[0].getInfo() << endl;
    delete[] arr2;

    Pixel p3 = {25, 127, 229};

    return 0;
}
