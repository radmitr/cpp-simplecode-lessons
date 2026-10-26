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
