# 27. Копия объекта, `std::ref` и лямбда

C++17. Продолжение [урока 05](../../lesson-05-class-methods/README.md).
Нужны методы класса, ссылки и `std::thread`. Это дополнительный пример вне курса.

`MyClass` хранит счётчик `total`. Метод `doWork2(123)` прибавляет к нему `123`.
[main.cpp](main.cpp) последовательно проверяет три способа запуска:

1. `std::thread a(&MyClass::doWork2, m, 123)` сохраняет копию `m`.
   Метод меняет копию, поэтому исходный `m.total` остаётся `0`.
2. `std::thread b(&MyClass::doWork2, std::ref(m), 123)` хранит ссылку
   на исходный объект. После `b.join()` его счётчик равен `123`.
3. Лямбда `[&m]() { m.doWork2(123); }` обращается к тому же объекту.
   После `c.join()` счётчик равен `246`.

~~~text
After copy: 0
After std::ref: 123
After lambda: 246
~~~

`&MyClass::doWork2` указывает метод, `std::ref(m)` задаёт исходный объект,
`[&m]` захватывает ссылку внутри лямбды. `std::ref` объявлен в `<functional>`.

Каждый поток присоединяется до следующего изменения или чтения счётчика.
Одновременного доступа к `m.total` здесь нет. Ссылка не продлевает жизнь объекта:
`m` должен существовать до завершения использующего его потока.
Копирование класса с указателями или `shared_ptr` не обязательно копирует
целые связанные объекты — это зависит от операций копирования самого класса.

## Сборка и запуск

Откройте `main.cpp`: **F5** — с отладчиком, **Ctrl+F5** — без отладчика.
Можно открыть корень проекта или папку этого бонуса.

Из корня, Linux:

~~~bash
bash scripts/build-linux.sh multithreading/bonus/27-class-method-arguments/main.cpp
./build/multithreading/bonus/27-class-method-arguments/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh multithreading/bonus/27-class-method-arguments/main.cpp
& .\build\multithreading\bonus\27-class-method-arguments\main.exe
~~~

Ввод не нужен. Программа возвращает `0` при верном результате,
`1` при нарушении встроенных проверок.
[Бонусы раздела](../README.md) · [Все уроки](../../../LESSONS.md).
