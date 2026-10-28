#include "String.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
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

void runComprehensiveTests()
{
    std::cout << "=== Всеобъемлющее тестирование String ===" << std::endl << std::endl;

    // 1. Тестирование всех конструкторов
    std::cout << "1. Тест конструкторов:" << std::endl;
    {
        String s1;                    // По умолчанию
        String s2("Hello");           // Из C-строки
        String s3 = s2;               // Копирования
        String s4 = std::move(s2);    // Перемещения
        String s5 = "Hi";             // Неявное преобразование через конструктор: String(const char* str)

        assert(s1.empty());
        assert(s2.empty());           // После перемещения
        assert(s3 == "Hello");
        assert(s4 == "Hello");
        std::cout << "   ✓ Конструкторы работают" << std::endl;
    }

    // 2. Тест операторов присваивания
    std::cout << "2. Тест операторов присваивания:" << std::endl;
    {
        String s1, s2("Hello"), s3("World");
        s1 = s2;                     // Копирующее
        assert(s1 == "Hello");

        s2 = std::move(s3);          // Перемещающее
        assert(s2 == "World");
        assert(s3.empty());
        std::cout << "   ✓ Операторы присваивания работают" << std::endl;
    }

    // 3. Тест конкатенации
    std::cout << "3. Тест конкатенации:" << std::endl;
    {
        String s1("Hello"), s2(" World");
        String s3 = s1 + s2;
        assert(s3 == "Hello World");

        s1 += s2;
        assert(s1 == "Hello World");
        std::cout << "   ✓ Конкатенация работает" << std::endl;
    }

    // 4. Тест сравнения
    std::cout << "4. Тест сравнения:" << std::endl;
    {
        String a("apple"), b("banana"), c("apple");
        assert(a == c);
        assert(a != b);
        assert(a < b);
        assert(b > a);
        std::cout << "   ✓ Сравнение работает" << std::endl;
    }

    // 5. Тест оператора []
    std::cout << "5. Тест оператора []:" << std::endl;
    {
        String s("Hello");
        assert(s[0] == 'H');
        s[0] = 'h';
        assert(s[0] == 'h');

        const String cs("World");
        assert(cs[0] == 'W');
        std::cout << "   ✓ Оператор [] работает" << std::endl;
    }

    // 6. Тест find и substr
    std::cout << "6. Тест find и substr:" << std::endl;
    {
        String s("Hello World");
        assert(s.find("World") == 6);
        assert(s.find("XYZ") == String::npos);
        assert(s.substr(6, 5) == "World");
        assert(s.substr(6) == "World");
        std::cout << "   ✓ Find и substr работают" << std::endl;
    }

    // 7. Тест replace
    std::cout << "7. Тест replace:" << std::endl;
    {
        String s("Hello World");
        s.replace(6, 5, "Universe");
        assert(s == "Hello Universe");
        std::cout << "   ✓ Replace работает" << std::endl;
    }

    // 8. Тест toUpper/toLower
    std::cout << "8. Тест toUpper/toLower:" << std::endl;
    {
        String s("Hello World");
        assert(s.toUpper() == "HELLO WORLD");
        assert(s.toLower() == "hello world");
        std::cout << "   ✓ toUpper/toLower работают" << std::endl;
    }

    // 9. Тест startsWith/endsWith
    std::cout << "9. Тест startsWith/endsWith:" << std::endl;
    {
        String s("Hello World");
        assert(s.startsWith("Hello"));
        assert(s.endsWith("World"));
        assert(!s.startsWith("World"));
        assert(!s.endsWith("Hello"));
        std::cout << "   ✓ startsWith/endsWith работают" << std::endl;
    }

    // 10. Тест итераторов
    std::cout << "10. Тест итераторов:" << std::endl;
    {
        String s("Hello");
        std::vector<char> chars(s.begin(), s.end());
        assert(chars.size() == 5);
        assert(chars[0] == 'H');

        // Range-based for
        int count = 0;
        for (char c : s)
        {
            (void)c;
            count++;
        }
        assert(count == 5);
        std::cout << "   ✓ Итераторы работают" << std::endl;
    }

    // 11. Тест методов
    std::cout << "11. Тест методов:" << std::endl;
    {
        String s("Hello");
        assert(s.length() == 5);
        assert(!s.empty());
        // Используем просто strcmp, а не std::strcmp
        assert(s == "Hello");

        s.clear();
        assert(s.empty());
        assert(s.length() == 0);
        std::cout << "   ✓ Методы работают" << std::endl;
    }

    // 12. Тест ввода/вывода
    std::cout << "12. Тест ввода/вывода:" << std::endl;
    {
        // --- Тест operator>> (читает слово до пробела) ---
        {
            std::stringstream ss;
            ss << "Hello World Test";

            String s1, s2, s3;
            ss >> s1 >> s2 >> s3;
            assert(s1 == "Hello");
            assert(s2 == "World");
            assert(s3 == "Test");
        }

        // --- Тест operator<< (вывод) ---
        {
            String s("Output Test");
            std::stringstream ss;
            ss << s;
            assert(ss.str() == "Output Test");
        }

        // --- Тест getline (читает всю строку до \n) ---
        {
            std::stringstream ss;
            ss << "Line with spaces and\ttabs\nNext line";

            String line;
            ::getline(ss, line); // :: чтобы вызвать ваш getline, а не std::getline

            assert(line == "Line with spaces and\ttabs");

            // Проверим, что можно прочитать и следующую строку
            ::getline(ss, line);
            assert(line == "Next line");
        }

        // --- Тест связки: вывод → getline → вывод ---
        {
            String original("Full line with spaces");
            std::stringstream ss;

            ss << original;           // вывод
            String restored;
            ::getline(ss, restored);  // чтение всей строки
            ss.str(""); ss.clear();   // сброс
            ss << restored;           // вывод обратно

            assert(ss.str() == "Full line with spaces");
        }

        std::cout << "   ✓ Ввод/вывод работают" << std::endl;
    }

    std::cout << std::endl << "=== Все тесты пройдены успешно! ===" << std::endl;
}

int main(void)
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    try
    {
        runComprehensiveTests();

        std::cout << std::endl << "=== Демонстрация ===" << std::endl;

        String s1("Hello");
        String s2(", world!");
        String s3 = s1 + s2;

        std::cout << "Создание: " << s1 << std::endl;
        std::cout << "Конкатенация: " << s3 << std::endl;
        std::cout << "Верхний регистр: " << s3.toUpper() << std::endl;
        std::cout << "Нижний регистр: " << s3.toLower() << std::endl;
        std::cout << "Начинается с 'Hello': " << std::boolalpha << s3.startsWith("Hello") << std::endl;
        std::cout << "Длина: " << s3.length() << std::endl;

        std::cout << "Посимвольно: ";
        for (char c : s3)
        {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
