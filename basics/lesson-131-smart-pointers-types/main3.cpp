// C++11 — std::unique_ptr, std::move, release() и reset().
#include <iostream>
#include <memory>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

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
