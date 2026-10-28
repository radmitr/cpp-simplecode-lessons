#include <iostream>

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

class TestClass
{
public:
    int& operator[](size_t index)
    {
        return arr[index];
    }

private:
    int arr[5]{5, 44, 4, 987, 69};
};

int main(void)
{
    setupConsoleEncoding();

    TestClass a;

    cout << a[1] << endl;
    a[1] = 100;
    cout << a[1] << endl;

    return 0;
}
