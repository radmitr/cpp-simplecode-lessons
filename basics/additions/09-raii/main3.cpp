// C++98 — деструкторы локальных объектов и владение памятью.
#include <iostream>

class Buffer
{
    int id_;
    int* data_;
    Buffer(const Buffer&); // Копирование пока запрещено через закрытые объявления.
    Buffer& operator=(const Buffer&);
public:
    Buffer(int id, int size) : id_(id), data_(new int[size])
    {
        for (int i = 0; i < size; ++i)
            data_[i] = i;
        std::cout << "Created " << id_ << '\n';
    }
    ~Buffer()
    {
        delete[] data_;
        std::cout << "Destroyed " << id_ << '\n';
    }
};

int main()
{
    {
        Buffer first(1, 3);
        Buffer second(2, 4);
        std::cout << "Leaving block\n";
    }
    std::cout << "After block\n";
    std::cout << "OK moved-example-080\n";
}
