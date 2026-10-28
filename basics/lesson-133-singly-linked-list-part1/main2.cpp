#include <iostream>
#include <memory>

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

template<typename T>
class List
{
public:
    List();
    ~List();

    void push_back(T data);
    void print() const;
    T& operator[](const int index);

    int getSize()
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

    int size;
    Node* head;
};

template<typename T>
List<T>::List()
{
    size = 0;
    head = nullptr;
}

template<typename T>
List<T>::~List()
{
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

template<typename T>
void List<T>::print() const
{
    Node* current = head;
    while (current)
    {
        cout << current->data << " ";
        current = current->pNext;
    }
    cout << endl;
}

template <typename T>
T& List<T>::operator[](const int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head;

    for (int i = 0; i < index; ++i)
    {
        current = current->pNext;
    }

    return current->data;
}

int main(void)
{
    setupConsoleEncoding();

    List<int> list;

    cout << "Введите размер списка: ";
    int numbersCount;
    cin >> numbersCount;

    for (int i = 0; i < numbersCount; i++)
    {
        list.push_back(rand() % 100);
    }

    for (int i = 0; i < list.getSize(); i++)
    {
        cout << "list[" << i << "] = " << list[i] << endl;
    }

    return 0;
}
