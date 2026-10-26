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

private:
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

    Image::Pixel pixel(25, 127, 229);
    cout << pixel.getInfo() << endl;

    return 0;
}
