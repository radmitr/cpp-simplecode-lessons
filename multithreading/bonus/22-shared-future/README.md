# 22. `std::shared_future`

C++17. Продолжение [promise/future](../09-promise-future/):
один производитель публикует результат, а три потребителя получают его.

## `main.cpp`: одни настройки для всех

~~~cpp
std::promise<Settings> promise;
std::shared_future<Settings> settings = promise.get_future().share();
~~~

Сокращённый фрагмент; полный пример: [main.cpp](main.cpp).

`get_future()` получает `future`, связанный с `promise`. `share()` передаёт его
состояние в `shared_future`. Исходный `future` после `share()` уже не содержит
этого состояния; здесь временный `future` сразу уничтожается.

Лямбда захватывает `settings` по значению. Каждый поток получает собственную
копию `shared_future`, но все копии ссылаются на одно общее состояние.
Копируется средство доступа к результату, а не отдельная загрузка настроек.

~~~cpp
const Settings& received = settings.get();
~~~

Сокращённый фрагмент; полный пример: [main.cpp](main.cpp).

`get()` ждёт готовности, если производитель ещё не вызвал `set_value()`.
Если результат уже опубликован, `get()` возвращается без ожидания его подготовки.
Уведомления вручную не нужны: `promise` и `future` согласуют готовность сами.

`promise.set_value(Settings{4, "localhost"})` публикует настройки один раз.
Все три работника получают localhost и `maxConnections == 4`.
В `main` `get()` вызывается ещё два раза:

~~~text
Main get #1: 4
Main get #2: 4
~~~

У обычного `std::future` вызов `get()` потребляет состояние, поэтому повторно
получать результат через тот же `future` нельзя. У `shared_future` `get()` можно
вызывать многократно. Для `Settings` он возвращает `const Settings&`;
ссылка действительна, пока общее состояние удерживается владельцами.

В примере каждый поток использует свою копию `shared_future`.
Полученные настройки только читаются. `shared_future` не делает произвольное
изменение объекта результата потокобезопасным.
`outputMtx` нужен для цельных строк консоли.

## `main2.cpp`: одно исключение для всех

Вместо `set_value()` производитель вызывает:

~~~cpp
promise.set_exception(
    std::make_exception_ptr(std::runtime_error("Configuration unavailable")));
~~~

Сокращённый фрагмент; полный пример: [main2.cpp](main2.cpp).

Каждый `get()` повторно выбрасывает сохранённое исключение.
Каждый работник обрабатывает его своим `catch`:

~~~text
Workers that received the exception: 3
~~~

Сами строки Worker могут идти в любом порядке.
Исключение не исчезает после первого потребителя.

## Сборка и запуск

Откройте `main.cpp`, `main2.cpp` или `main3.cpp`: **F5** — с отладчиком,
**Ctrl+F5** — без отладчика.
Из корня репозитория на Linux:

~~~bash
bash scripts/build-linux.sh multithreading/bonus/22-shared-future/main.cpp
./build/multithreading/bonus/22-shared-future/main
~~~

На Windows из MSYS2 Bash:

~~~bash
bash scripts/build-windows.sh multithreading/bonus/22-shared-future/main.cpp
./build/multithreading/bonus/22-shared-future/main.exe
~~~

Для исключения замените `main.cpp`/`main` на `main2.cpp`/main2.
После добавления исходников обновите IntelliSense через задачу
C/C++: Update IntelliSense.

[shared_future в проекте стандарта](https://eel.is/c++draft/futures.shared.future).
[Все бонусы](../README.md).

## `main3.cpp`: `shared_future` от `std::async`

Один `future` передаёт результат одному получателю через однократный `get`.
`shared_future` позволяет нескольким владельцам ждать и читать одно состояние.
Он не запускает производителя повторно.

~~~cpp
auto result = std::async(std::launch::async, sum, 2, 5);
auto shared = result.share();
~~~

Полная программа: [main3.cpp](main3.cpp). Здесь производителем является
`std::async`; `main.cpp`/`main2.cpp` публикуют результат через `promise`.
`share()` передаёт доступ: исходный `result.valid()` становится `false`.
Два вызова `shared.get()` возвращают ссылки на одно сохранённое число `7`.
Программа сравнивает их адреса и не вызывает функцию второй раз.

~~~text
Original future valid: false
First get: 7
Second get: 7
Same stored value: true
~~~

У обычного `std::shared_future<T>` метод `get()` возвращает `const T&`.
Для `void` и ссылочных специализаций тип результата отличается.
Этот вариант не требует ввода и возвращает `0` при верном результате, `1` при ошибке.
Для его запуска замените `main.cpp`/`main` на `main3.cpp`/`main3`.

`wait` также может использоваться для сигнала без извлечения значения:
практический пример `gate.wait` есть в бонусе `11/main2.cpp`.
Подробности `get`/`wait`/таймаутов и поведения deferred —
в [бонусе 05](../05-future-async/README.md).
