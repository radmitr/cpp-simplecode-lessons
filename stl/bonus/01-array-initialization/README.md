# 01. `std::array`: инициализация, копия и нулевой размер

C++17. После [урока 06](../../lesson-06-stl-array/README.md).
Нужны массивы, шаблоны и ссылки. Это дополнительный пример вне курса.

Полный исходник: [main.cpp](main.cpp).

~~~cpp
std::array<int, 5> a{};
a.at(0) = 42;
auto copy = a;
copy.at(0) = 7;
~~~

`a{}` инициализирует все пять элементов нулями. Изменение `a.at(0)` оставляет
последний элемент нулевым. Копирование создаёт самостоятельные элементы:
присваивание через `copy` не меняет исходный массив.

~~~text
Original: 42, last=0
Copy: 7
Empty: true, begin equals end: true
~~~

Последняя строка относится к `std::array<int, 0>`. Такой тип допустим:
`empty()` возвращает `true`, `begin() == end()`.
Элементов нет, поэтому `front()`, `back()` и разыменование `begin()`
использовать нельзя. Проверять пустоту до доступа — часть контракта программы,
а не гарантия, что любой ошибочный доступ обязательно вызовет исключение.

## Сборка и запуск

Откройте `main.cpp`: **F5** — с отладчиком, **Ctrl+F5** — без отладчика.
Можно открыть корень проекта или папку этого бонуса.

Из корня, Linux:

~~~bash
bash scripts/build-linux.sh stl/bonus/01-array-initialization/main.cpp
./build/stl/bonus/01-array-initialization/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh stl/bonus/01-array-initialization/main.cpp
& .\build\stl\bonus\01-array-initialization\main.exe
~~~

Ввод не нужен. Программа возвращает `0` при верном результате,
`1` при нарушении встроенных проверок.
[Бонусы раздела](../README.md) · [Все уроки](../../../LESSONS.md).
