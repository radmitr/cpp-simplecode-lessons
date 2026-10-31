# 01. Префиксный и постфиксный `operator--`

C++17. После [урока 86 про увеличение](../../lesson-086-oop-operator-overloading-increment-decrement/README.md).
Нужны перегрузка операторов, ссылки и копирование объектов. Это дополнение вне курса.

В [main.cpp](main.cpp) `Point` содержит координаты `x` и `y`.
Обе перегрузки уменьшают каждую координату на единицу:

- `Point& operator--()` сначала меняет объект и возвращает `*this` по ссылке.
- `Point operator--(int)` сохраняет копию прежнего состояния, уменьшает объект
  и возвращает сохранённую копию. Параметр `int` отличает постфиксную форму;
  при записи `a--` аргумент вручную не передаётся.

Начальное `a` равно `(5, 1)`. `Point& reference = --a` меняет его на `(4, 0)`.
`reference` обозначает сам `a`, а не самостоятельную копию.
Затем `Point previous = a--` получает прежнее `(4, 0)`,
а `a` становится `(3, -1)`.

~~~text
Prefix: 4, 0
Postfix returned: 4, 0
Current: 3, -1
~~~

Итоговая проверка сравнивает и координаты, и адреса `reference`/`a`.
Если старое значение не требуется, префиксная форма обычно проще:
постфиксная может создавать дополнительную копию.

## Сборка и запуск

Откройте `main.cpp`: **F5** — с отладчиком, **Ctrl+F5** — без отладчика.
Можно открыть корень проекта или папку этого бонуса.

Из корня, Linux:

~~~bash
bash scripts/build-linux.sh oop/bonus/01-decrement-operators/main.cpp
./build/oop/bonus/01-decrement-operators/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh oop/bonus/01-decrement-operators/main.cpp
& .\build\oop\bonus\01-decrement-operators\main.exe
~~~

Ввод не нужен. Программа возвращает `0` при верном результате,
`1` при нарушении встроенных проверок.
[Бонусы раздела](../README.md) · [Все уроки](../../../LESSONS.md).
