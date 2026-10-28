#include <cstring>
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

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

class CowString
{
  private:
    struct Data
    {
        char *buffer;
        size_t size;
        size_t refCount;

        Data(const char *str)
        {
            size = strlen(str) + 1;
            buffer = new char[size];
            strcpy(buffer, str);
            refCount = 1;
            std::cout << "Создан буфер: " << buffer << std::endl;
        }

        ~Data()
        {
            delete[] buffer;
            std::cout << "Уничтожен буфер" << std::endl;
        }

        void addRef() { ++refCount; }
        void release()
        {
            if (--refCount == 0)
            {
                delete this;
            }
        }
    };

    Data *data;

    // Вспомогательный метод для копирования при записи
    void detach()
    {
        // Если ссылок больше 1, значит нужно создать копию
        if (data->refCount > 1)
        {
            Data *oldData = data;
            data = new Data(oldData->buffer);
            oldData->release();
        }
    }

  public:
    // Конструктор
    CowString(const char *str = "")
    {
        data = new Data(str);
    }

    // Конструктор копирования (COW здесь!)
    CowString(const CowString &other)
    {
        data = other.data;
        data->addRef(); // Просто увеличили счётчик, данные не копировали!
        std::cout << "Копия (без копирования данных)" << std::endl;
    }

    // Деструктор
    ~CowString()
    {
        data->release();
    }

    // Оператор присваивания
    CowString &operator=(const CowString &other)
    {
        if (this != &other)
        {
            data->release();
            data = other.data;
            data->addRef();
        }
        return *this;
    }

    // Чтение (не требует копирования)
    char get(size_t index) const
    {
        return data->buffer[index];
    }

    // Запись (требует копирования!)
    void set(size_t index, char c)
    {
        detach(); // Ключевой момент: копируем перед изменением
        data->buffer[index] = c;
    }

    // Оператор [] для чтения и записи
    char &operator[](size_t index)
    {
        detach(); // Копируем перед записью
        return data->buffer[index];
    }

    // Для const объектов - только чтение
    const char &operator[](size_t index) const
    {
        return data->buffer[index];
    }

    void print() const
    {
        std::cout << data->buffer << " (refs: " << data->refCount << ")" << std::endl;
    }
};

// Демонстрация работы
int main()
{
    setupConsoleEncoding();

    std::cout << "Создаём исходную строку s1: ";
    CowString s1("Hello");
    s1.print();

    std::cout << "\nСоздаём s2 как копию s1 (COW): ";
    CowString s2(s1); // Копирования данных НЕТ!
    s1.print();
    s2.print();

    std::cout << "\nЧитаем из s2 (копирования нет): ";
    char c = s2.get(0);
    std::cout << "char: " << c << std::endl;
    s1.print();
    s2.print();

    std::cout << "\nИзменяем s2 (произойдёт копирование!): ";
    s2.set(0, 'J'); // ТОЛЬКО СЕЙЧАС данные копируются
    s1.print();
    s2.print();

    std::cout << "\nСоздаём s3 = s2 (опять без копирования): ";
    CowString s3 = s2;
    s2.print();
    s3.print();

    std::cout << "\nИзменяем s3 (копирование): ";
    s3.set(1, 'a');
    s2.print();
    s3.print();

    return 0;
}
