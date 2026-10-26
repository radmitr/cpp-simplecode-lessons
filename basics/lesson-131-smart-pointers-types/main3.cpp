#include <iostream>
#include <memory>

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

int main(void)
{
    setupConsoleEncoding();

    int* rawPointer = new int(5);

    unique_ptr<int> p1(rawPointer);

    //unique_ptr<int> p2(p1); // cannot be referenced -- it is a deleted function
    unique_ptr<int> p2;
    p2 = move(p1);
    p1.swap(p2);

    int* rawPointer1 = p1.get();
    cout << "Адрес: " << rawPointer1 << endl;
    cout << "Значение: " << *rawPointer1 << endl;

    p1.release();

    unique_ptr<int> p3(rawPointer);
    p3.reset();

    return 0;
}
