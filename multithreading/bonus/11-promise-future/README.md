# 11. `std::promise` и `std::future`

## Версия C++

захват с инициализацией — **C++14**.
`std::thread`, `std::future`, `std::promise`, `std::move`, `std::chrono` — **C++11**.
`std::exception`, `std::invalid_argument`, `std::boolalpha` — **C++98**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.

## Что изучаем

Продолжение [future/async](../12-future-async/README.md).
Здесь `std::thread` создаём самостоятельно. Рабочий поток передаёт значение
или исключение через `std::promise`, а главный получает его через `std::future`.

## Примеры

- [main.cpp](main.cpp).
- [main2.cpp](main2.cpp).
- [main3.cpp](main3.cpp).

Выбирайте один исходник с `main()`; варианты запускаются отдельно.

## Как это работает

Оба объекта обращаются к одному месту хранения результата — **общему состоянию**.
`promise` предоставляет результат, `future` ожидает и получает его.
Эта пара сама не запускает поток и не завершает уже созданный поток.

### `main.cpp`: передать значение или исключение

Полная программа: [main.cpp](main.cpp).

1. Главный поток создаёт `std::promise<int> output`.
2. `output.get_future()` получает связанный с ним `std::future<int>`.
3. `std::move(output)` передаёт `promise` рабочей функции по значению.
   Копирование запрещено, перемещение разрешено; главный сохраняет `future`.
4. `calculate` вычисляет сумму. `output.set_value(a + b)` сохраняет число
   и разрешает ожидающим получить его.
5. `result.get()` в главном потоке дожидается результата и возвращает число.
6. `worker.join()` дожидается окончания всей рабочей функции.

Для `2` и `5` результат равен `7`. Во втором запуске первый аргумент равен `-2`.
Рабочая функция выбрасывает `std::invalid_argument`, ловит его через `catch (...)`,
а `set_exception(std::current_exception())` сохраняет текущее исключение.
Главный поток получает его из `get()` и обрабатывает своим `catch`.

~~~text
Main: waiting for calculate(2, 5)
Result: 7
Main: waiting for calculate(-2, 5)
Caught: Arguments must be non-negative
~~~

Если исключение просто выйдет из функции `std::thread`, пара `promise/future`
сама его не перехватит: будет вызван `std::terminate()`.
Работающий пример обоих случаев завершения —
[05/main8.cpp](../12-future-async/main8.cpp).

### `main2.cpp`: результат готов раньше завершения потока

Полная программа: [main2.cpp](main2.cpp).

Работник вызывает `output.set_value(7)` и затем ждёт отдельного разрешения
`permission`. Пока главный поток не подал этот сигнал, работник не может
закончить функцию. Это позволяет проверить порядок без предположений о скорости.

Главный поток дважды вызывает `result.wait()`, затем один раз `get()`.
`wait()` только ждёт готовности и не забирает число.
После `get()` главный уже получил `7`, но `finished` пока равен `false`.

Затем главный поток разрешает продолжение через `resume.set_value()` и вызывает
`worker.join()`. После `join()` рабочая функция точно закончена.

~~~text
Result: 7
Worker finished after get: false
Worker finished after join: true
~~~

Поэтому `get()` и `join()` не взаимозаменяемы.
Уничтожение `future` от `promise` тоже не выполняет `join()`.
`std::atomic<bool>` здесь позволяет безопасно наблюдать флаг завершения;
он не управляет временем жизни потока.

### `main3.cpp`: ошибки использования `promise`

Полная программа: [main3.cpp](main3.cpp).

- Повторный `get_future()` у того же `promise` вызывает `std::future_error`
  с кодом `future_already_retrieved`. Несколько читателей организуют через
  [shared_future](../13-shared-future/README.md).
- Повторный `set_value()` после публикации результата вызывает
  `promise_already_satisfied`. То же ограничение действует на выбор
  между `set_value()` и `set_exception()`: результат устанавливают один раз.
- Если `promise` уничтожился без значения и исключения, его `future`
  получает ошибку `broken_promise`. Ожидание не остаётся бесконечным.

Все три ошибки перехватываются. Программа сравнивает именно коды ошибок,
а не текст `what()`, который может отличаться между библиотеками.
Изначальное число `7` остаётся доступно через первый `future`.

~~~text
Second get_future: future_already_retrieved
Second set_value: promise_already_satisfied
Abandoned result: broken_promise
Original result: 7
~~~

После `future::get()` проверяют `valid()`. Повторный `get()` у невалидного
`future` не используют как способ получить демонстрационное исключение.

## Сборка и запуск

[Запуск в VS Code](../../../README.md#сборка-и-запуск-в-vs-code).

Выберите `main.cpp`, `main2.cpp` или `main3.cpp`.
**F5** — запуск с отладчиком, **Ctrl+F5** — без отладчика.

Из корня проекта, Linux:

~~~bash
bash scripts/build-linux.sh multithreading/bonus/11-promise-future/main2.cpp
./build/multithreading/bonus/11-promise-future/main2
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh multithreading/bonus/11-promise-future/main2.cpp
& .\build\multithreading\bonus\11-promise-future\main2.exe
~~~

Замените имя для другого варианта. Ввод не нужен, успешный код завершения —
`0`, нарушение встроенной проверки даёт `1`.
Для таймаутов и отложенного запуска смотрите [`std::future` и `std::async`: запуск, ожидание и исключения](../12-future-async/README.md).

[Все бонусы](../README.md) ·
[`std::promise`](https://eel.is/c++draft/futures.promise).

## Связанные темы и источники

[Версии C++](../../../docs/cpp-versions.md) · [Как читать справочники](../../../docs/references.md).
