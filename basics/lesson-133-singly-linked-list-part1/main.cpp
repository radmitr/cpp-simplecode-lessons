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

    list.push_back(5);
    list.push_back(10);
    list.push_back(22);

    list.print();
    cout << "size = " << list.getSize() << endl;

    for (int i = 0; i < list.getSize(); i++)
    {
        cout << "list[" << i << "] = " << list[i] << endl;
    }

    cout << "list[1000] = " << list[1000] << endl; //what():  Index out of range

    return 0;
}
