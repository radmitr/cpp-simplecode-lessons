#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

template<typename T>
class List
{
public:
    List();
    List(const List& other);
    List(List&& other) noexcept;
    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;
    ~List();

    T& operator[](const size_t index);
    void pop_front();
    void pop_back();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, size_t index);
    void removeAt(size_t index);
    ssize_t findFirst(const T& value) const;
    void clear();
    void print() const;

    size_t getSize()
    {
        return size;
    }

private:
    class Node
    {
    public:
        Node(T data = T(), Node *pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
        }

        Node* pNext;
        T data;
    };

    size_t size;
    Node* head;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const List<U>& list);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, List<U>& list);
};

template<typename T>
List<T>::List()
{
    size = 0;
    head = nullptr;
}

template<typename T>
List<T>::List(const List<T>& other)
    : size(0), head(nullptr)
{
    Node* current = other.head;
    while (current)
    {
        push_back(current->data);
        current = current->pNext;
    }
}

template<typename T>
List<T>::List(List<T>&& other) noexcept
    : size(other.size), head(other.head)
{
    other.head = nullptr;
    other.size = 0;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
    if (this != &other)
    {
        clear();
        Node* current = other.head;
        while (current)
        {
            push_back(current->data);
            current = current->pNext;
        }
    }
    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& other) noexcept
{
    if (this != &other)
    {
        clear();
        head = other.head;
        size = other.size;
        other.head = nullptr;
        other.size = 0;
    }
    return *this;
}

template<typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
T& List<T>::operator[](const size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head;
    for (size_t i = 0; i < index; ++i)
    {
        current = current->pNext;
    }

    return current->data;
}

template <typename T>
void List<T>::pop_front()
{
    if (head)
    {
        Node* temp = head;
        head = head->pNext;
        delete temp;
        size--;
    }
}

template <typename T>
void List<T>::pop_back()
{
    if (size > 0)
    {
        removeAt(size - 1);
    }
}

template <typename T>
void List<T>::push_front(T data)
{
    head = new Node(data, head);
    size++;
}

template<typename T>
void List<T>::push_back(T data)
{
    if (head == nullptr)
    {
        head = new Node(data);
    }
    else
    {
        Node *current = head;
        while (current->pNext)
        {
            current = current->pNext;
        }
        current->pNext = new Node(data);
    }
    size++;
}

template <typename T>
void List<T>::insert(T data, size_t index)
{
    if (index > size)
    {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0)
    {
        head = new Node(data, head);
    }
    else
    {
        Node* previous = head;
        for (size_t i = 0; i < index - 1; ++i)
        {
            previous = previous->pNext;
        }

        Node* newNode = new Node(data, previous->pNext);
        previous->pNext = newNode;
    }
    size++;
}

template <typename T>
void List<T>::removeAt(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0)
    {
        pop_front();
    }
    else
    {
        Node* previous = head;
        for (size_t i = 0; i < index - 1; ++i)
        {
            previous = previous->pNext;
        }

        Node* toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;

        delete toDelete;
        size--;
    }
}

template <typename T>
ssize_t List<T>::findFirst(const T& value) const
{
    Node* current = head;
    size_t index = 0;
    while (current)
    {
        if (current->data == value)
        {
            return index;
        }
        current = current->pNext;
        index++;
    }
    return -1;
}

template <typename T>
void List<T>::clear()
{
    while (head)
    {
        Node* oldHead = head;
        head = head->pNext;
        delete oldHead;
    }
    size = 0;
}

template<typename T>
void List<T>::print() const
{
    Node* current = head;
    while (current)
    {
        std::cout << current->data << " ";
        current = current->pNext;
    }
    std::cout << std::endl;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
    if (list.size == 0)
    {
        os << "[]";
        return os;
    }

    os << "[";
    typename List<T>::Node* current = list.head;
    while (current)
    {
        os << current->data;
        if (current->pNext)
        {
            os << ", ";
        }
        current = current->pNext;
    }
    os << "]";
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, List<T>& list)
{
    list.clear();
    std::string line;
    std::getline(is, line);

    if (line.empty())
    {
        return is;
    }

    std::istringstream iss(line);
    T value;
    while (iss >> value)
    {
        list.push_back(value);
    }
    return is;
}

int main(void)
{
    setupConsoleEncoding();

    List<int> list;
    list.push_front(5);
    list.push_front(7);
    list.push_front(101);
    list.print();

    list.insert(50, 1);
    list.print();

    list.removeAt(2);
    list.print();

    list.pop_back();
    list.print();

    list.push_back(0);
    list.push_back(-10);
    list.push_back(-101);
    list.print();

    List<int> list2 = list;
    std::cout << list2 << std::endl;
    list2.print();

    std::cout << "Введите значения списка: " << std::endl;
    List<int> list3;
    std::cin >> list3;
    std::cout << list3 << std::endl;

    int value;
    std::cout << "Введите число для поиска: " << std::endl;
    std::cin >> value;

    std::cout << "Ищем первое попавшееся число: " << value << std::endl;
    ssize_t idx = list3.findFirst(value);
    if (idx >= 0)
    {
        std::cout << "Нашли число " << value << " под индексом: " << idx << std::endl;
    }
    else
    {
        std::cout << "Не нашли число " << value << std::endl;
    }

    return 0;
}
