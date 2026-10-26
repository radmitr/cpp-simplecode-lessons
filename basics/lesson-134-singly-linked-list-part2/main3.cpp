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

template<typename T>
class List
{
public:
    List();
    ~List();

    void pop_front();
    void push_back(T data);
    void clear();
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
    clear();
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

// template <typename T>
// void List<T>::clear()
// {
//     while (head)
//     {
//         pop_front();
//     }
// }

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

int main(void)
{
    setupConsoleEncoding();

    setupConsoleEncoding();

    List<int> list;
    list.push_back(55);
    list.push_back(11);
    list.push_back(2);

    cout << "Список до удаления: ";
    for (int i = 0; i < list.getSize(); i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;

    cout << endl << "Элементов в списке: " << list.getSize() << "\nВыполняю метод pop_front()" << endl << endl;
    list.pop_front();

    cout << "Список после удаления первого элемента: ";
    for (int i = 0; i < list.getSize(); i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;

    cout << endl << "Элементов в списке: " << list.getSize() << endl;

    return 0;
}
