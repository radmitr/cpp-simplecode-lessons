# 04. Результат или ошибка: `std::expected`

## Версия C++

`std::expected<T, E>`, `std::unexpected<E>` и `std::bad_expected_access<E>` —
**C++23**. `from_chars` — C++17. Сборка: **C++23**, GCC/libstdc++ 13+.
На Linux с GCC 11 нужен [дополнительный компилятор](../../../bonus/reflection/linux-setup.md);
сборка выберет `CXX_MODERN` по `gcc-min-version.txt`.

## Что изучаем

Операция может вернуть полезное значение **или описание ошибки**.
`expected<int, string>` хранит либо `int`, либо `string` с ошибкой.
Ошибка является обычным результатом вызова; выбрасывать её автоматически
не требуется. Нужны функции, шаблонные типы, строки и
[исключения](../../../exceptions/bonus/30-exception-types/README.md).

## Примеры

- [main.cpp](main.cpp): успешное/ошибочное состояние, `value()`, `error()`,
  `value_or()` и исключение при неверном доступе.
- [main2.cpp](main2.cpp): функция разбора положительного числа без
  выбрасывания исключения для ожидаемой ошибки формата.

## Как это работает

`std::expected<int, std::string> success = 42` создаёт результат с числом.
`std::unexpected(std::string("invalid number"))` явно обозначает ветку ошибки.
Это позволяет различать значение и ошибку даже при одинаковых типах `T` и `E`.

`if (result)` и `has_value()` проверяют наличие **значения**.
После положительной проверки `*result` даёт доступ к нему; `error()`
разрешён только в состоянии ошибки. `operator*` не является проверяемой
заменой `value()`: без значения его использовать нельзя.

`value()` возвращает значение, а при ошибке бросает `bad_expected_access<E>`.
В `main.cpp` исключение содержит нашу строку, доступную через `error.error()`.
`what()` даёт библиотечное описание, которое не обязано совпадать с этой строкой.
`value_or(0)` вместо исключения возвращает запасное `0` и не очищает ошибку.

В `main2.cpp` `from_chars` сообщает об ошибке кодом, затем функция переводит
её в понятный результат `expected`. Дополнительно проверяется, что разобрана
**вся** строка: `12abc` отвергается, хотя числовой префикс `12` найден.
Ошибка `-3` другая: число корректное, но не положительное.

`optional<T>` хранит значение или отсутствие; `expected<T,E>` ещё хранит
описание причины. `future<T>` представляет результат, который может быть
ещё не готов; `expected` сам по себе ничего не запускает и не ждёт.
У `expected<void,E>` успех означает отсутствие ошибки без отдельного значения.

## Сборка и запуск

[Запуск в VS Code](../../../README.md#сборка-и-запуск-в-vs-code).

Из корня, Linux:

~~~bash
bash scripts/build-linux.sh stl/bonus/04-expected/main.cpp
./build/stl/bonus/04-expected/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh stl/bonus/04-expected/main.cpp
& .\build\stl\bonus\04-expected\main.exe
~~~

Ввода и файлов нет. Успех — код `0`, неудачная проверка — `1`.
`main.cpp` печатает:

~~~text
Value: 42
Error: invalid number
Caught: invalid number
Fallback: 0
~~~

Для `main2.cpp` замените имя в обеих командах. Ожидается:

~~~text
12 -> 12
12abc -> not an integer
-3 -> must be positive
~~~

## Типичные ошибки

Читать `error()` при успехе или `*result` при ошибке; терять причину,
всегда заменяя её через `value_or`; предполагать, что `expected` запрещает
любые исключения. Выделение памяти для строки ошибки, например, всё ещё
может бросить `bad_alloc`.

## Связанные темы и источники

- [Стандартные и собственные исключения](../../../exceptions/bonus/30-exception-types/README.md).
- [Проверяемые числовые преобразования](../../../io/bonus/04-charconv/README.md).
- [Контракт `expected`](https://eel.is/c++draft/expected)
  и [`bad_expected_access`](https://eel.is/c++draft/expected.bad).
- [Версии C++](../../../docs/cpp-versions.md) · [Источники](../../../docs/references.md).
- [Бонусы STL](../README.md).
