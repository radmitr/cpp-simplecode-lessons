// C++98 — копирование, присваивание и деструктор.
// Само правило — рекомендация проектирования, а не отдельная фича стандарта.
#include <utility>
#include <algorithm>
#include <cstddef>
#include "../common/check.hpp"

class Buffer
{
    std::size_t size_;
    int* data_;
public:
    explicit Buffer(std::size_t size) : size_(size), data_(new int[size])
    {
        std::fill(data_, data_ + size_, 0);
    }
    ~Buffer() { delete[] data_; }

    Buffer(const Buffer& other) : size_(other.size_), data_(new int[other.size_])
    {
        std::copy(other.data_, other.data_ + size_, data_); // Копируем элементы, не указатель.
    }

    Buffer& operator=(const Buffer& other)
    {
        if (this != &other)
        {
            Buffer copy(other); // Если new бросит, исходный *this ещё не изменён.
            std::swap(size_, copy.size_);
            std::swap(data_, copy.data_);
        } // copy освобождает прежний массив *this.
        return *this;
    }

    int& operator[](std::size_t index) { return data_[index]; }
    const int& operator[](std::size_t index) const { return data_[index]; }
};

int main()
{
    try
    {
        Buffer first(2);
        first[0] = 7;
        Buffer second = first; // Конструктор копирования: создаём новый объект.
        second[0] = 9;
        Buffer third(1);
        third = first;         // Присваивание: объект уже существовал.
        first = first;         // Самоприсваивание должно сохранить данные.
        check(first[0] == 7 && second[0] == 9 && third[0] == 7, "deep copy failed");
        std::cout << first[0] << ' ' << second[0] << ' ' << third[0] << '\n';
        std::cout << "OK rule-of-three\n";
    } // Деструктор каждого объекта освобождает именно его собственный массив.
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
