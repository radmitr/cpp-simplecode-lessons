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

class Image
{
public:
    void getImageInfo()
    {
        for (size_t i = 0; i < LENGTH; i++)
        {
            cout << "#" << i << " " << pixels[i].getInfo() << endl;
        }
    }

private:
    class Pixel
    {
    public:
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

    static const int LENGTH = 5;

    Pixel pixels[LENGTH] {
        Pixel(0, 4, 64),
        Pixel(11, 50, 155),
        Pixel(100, 215, 71),
        Pixel(1, 254, 125),
        Pixel(201, 83, 253)
    };
};

int main(void)
{
    setupConsoleEncoding();

    Image img;
    img.getImageInfo();

    return 0;
}
