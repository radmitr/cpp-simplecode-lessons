# 22. compare_exchange: сравнить и заменить

## Версия C++

`std::thread`, `std::mutex`, `std::lock_guard`, `std::atomic`, `auto` — **C++11**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.

## Что изучаем

CAS (compare-and-`swap`) позволяет атомарно проверить ожидаемое
значение и заменить его новым. Это продолжение [atomic](../20-atomic/)
и [memory_order](../21-memory-order/).

## Примеры

- [main.cpp](main.cpp).
- [main2.cpp](main2.cpp).
- [main3.cpp](main3.cpp).

Выбирайте один исходник с `main()`; варианты запускаются отдельно.

## Как это работает

### `main.cpp`: два покупателя и последний товар

На складе stock == 1. Каждый покупатель пытается выполнить:

~~~cpp
int expected = 1;
const bool bought = stock.compare_exchange_strong(expected, 0);
~~~

Сокращённый фрагмент; полный пример: [main.cpp](main.cpp).

Для `int` смысл такой:

- если stock == `expected`, заменить stock на 0 и вернуть `true`;
- если значения не совпали, не менять stock, записать его фактическое
  значение в `expected` и вернуть `false`.

Сравнение и условная замена происходят как одна атомарная операция.
`expected` — локальная переменная каждого покупателя.

Один покупатель успешно меняет 1 на 0. Второй обнаруживает 0 вместо 1,
получает `false` и `expected == 0`. Например:

~~~text
Buyer 1: accepted; expected after CAS = 1
Buyer 2: rejected; expected after CAS = 0
Accepted orders: 1
Remaining items: 0
~~~

Победитель и порядок печати неизвестны. После успешного CAS `expected`
остаётся равен прежнему ожидаемому значению 1: это не копия нового stock.
`outputMtx` защищает только печать; остаток защищает сама атомарная операция.

Так писать недостаточно, даже если stock является `atomic`:

~~~cpp
if (stock.load() == 1)
{
    stock.store(0);
    // Между load() и store() другой покупатель тоже мог увидеть 1.
}
~~~

Сокращённый фрагмент; полный пример: [main.cpp](main.cpp).

Отдельные атомарные чтение и запись не делают всю проверку со списанием
неделимой.

### `main2.cpp`: повторные попытки через weak

Четыре потока делают по 500 попыток купить товар со склада на 1000 единиц.
`reserveOne()` загружает текущий остаток и пытается заменить `expected`
на `expected` - 1:

~~~cpp
while (expected > 0)
{
    if (stock.compare_exchange_weak(expected, expected - 1))
    {
        return true;
    }
}
~~~

Сокращённый фрагмент; полный пример: [main2.cpp](main2.cpp).

Если другой покупатель успел раньше, CAS обновит `expected`. Следующая
итерация пересчитает новое значение по обновлённому остатку.
Когда `expected == 0`, функция вернёт `false` и товар не спишется.

weak может вернуть `false` даже при совпадении значений — это ложный отказ.
Поэтому здесь он находится в цикле. strong не имеет такого ложного отказа
и удобен для одиночной попытки в `main.cpp`.

Ожидаемый итог:

~~~text
Purchase attempts: 2000
Accepted orders: 1000
Remaining items: 0
~~~

Используется стандартный порядок памяти seq_cst. CAS не заменяет мьютекс
для произвольного набора связанных данных; здесь изменяется один остаток.
Операции `std::atomic` не обязаны быть `lock-free` на любой платформе.

### `main3.cpp`: атомарные операции, но неверный алгоритм

Полная программа: [main3.cpp](main3.cpp). Она выполняет показанную выше
раздельную проверку `load()` и запись `store()`. Каждый покупатель сначала
видит `stock == 1`, затем ждёт, пока второй тоже выполнит проверку.
Только после этого оба записывают `0` и считают свою покупку принятой.

Ожидается `Accepted with separate load/store: 2` и `Remaining items: 0`.
Это намеренная **логическая ошибка**: все обращения атомарны, гонки данных
нет, но проверка и замена не объединены в одну операцию.
В `main.cpp` атомарный `compare_exchange_strong` допускает ровно одну покупку.
Порядок в `main3.cpp` задан сигналами `promise/shared_future`, а не случайными
паузами. Ввод не нужен, код `0` подтверждает ожидаемую демонстрацию, `1` — ошибку.

## Сборка и запуск

[Запуск в VS Code](../../../README.md#сборка-и-запуск-в-vs-code).

Откройте `main.cpp`, `main2.cpp` или `main3.cpp` и нажмите F5 либо Ctrl+F5.
Из корня репозитория на Linux:

~~~bash
bash scripts/build-linux.sh multithreading/additions/22-compare-exchange/main.cpp
./build/multithreading/additions/22-compare-exchange/main
~~~

На Windows из MSYS2 Bash:

~~~bash
bash scripts/build-windows.sh multithreading/additions/22-compare-exchange/main.cpp
./build/multithreading/additions/22-compare-exchange/main.exe
~~~

Для цикла weak замените `main.cpp`/`main` на `main2.cpp`/`main2`.
После добавления исходников обновите IntelliSense через задачу
C/C++: Update IntelliSense.

[Операции atomic в проекте стандарта](https://eel.is/c++draft/atomics.types.operations).
[Все дополнения](../README.md).

Для демонстрации раздельных `load`/`store` замените в командах
`main.cpp`/`main` на `main3.cpp`/`main3`.

## Связанные темы и источники

[Версии C++](../../../docs/cpp-versions.md) · [Как читать справочники](../../../docs/references.md).
