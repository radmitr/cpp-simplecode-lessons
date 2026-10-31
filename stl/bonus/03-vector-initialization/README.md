# 03. `std::vector`: круглые и фигурные скобки

C++17. После [урока 01](../../lesson-01-stl-vector/README.md).
Нужны конструкторы и списки инициализации. Это сравнение дополняет курс.

Полный исходник: [main.cpp](main.cpp).

~~~cpp
std::vector<int> a(20);
std::vector<int> b{20};
std::vector<int> c(20, 55);
std::vector<int> d{20, 55};
~~~

`a(20)` вызывает конструктор с количеством элементов: создаются 20 нулей.
`b{20}` выбирает конструктор со списком значений: список содержит только число
`20`, поэтому размер равен `1`.

`c(20, 55)` задаёт количество и общее начальное значение: 20 элементов по `55`.
`d{20, 55}` содержит два заданных значения: `20` и `55`.

~~~text
a: size=20, first=0
b: size=1, first=20
c: size=20, first=55
d: size=2, first=20, last=55
~~~

При чтении инициализации учитывайте не только аргументы, но и вид скобок:
при подходящих элементах фигурные скобки предпочитают конструктор
`std::initializer_list`. Операции `reserve()` и `resize()` уже показаны
в исходном уроке; здесь они не повторяются.

## Сборка и запуск

Откройте `main.cpp`: **F5** — с отладчиком, **Ctrl+F5** — без отладчика.
Можно открыть корень проекта или папку этого бонуса.

Из корня, Linux:

~~~bash
bash scripts/build-linux.sh stl/bonus/03-vector-initialization/main.cpp
./build/stl/bonus/03-vector-initialization/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh stl/bonus/03-vector-initialization/main.cpp
& .\build\stl\bonus\03-vector-initialization\main.exe
~~~

Ввод не нужен. Программа возвращает `0` при верном результате,
`1` при нарушении встроенных проверок.
[Бонусы раздела](../README.md) · [Все уроки](../../../LESSONS.md).
