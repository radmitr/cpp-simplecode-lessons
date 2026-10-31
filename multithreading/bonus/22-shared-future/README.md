# 22. std::shared_future

C++17. Продолжение [promise/future](../09-promise-future/):
один производитель публикует результат, а три потребителя получают его.

## main.cpp: одни настройки для всех

~~~cpp
std::promise<Settings> promise;
std::shared_future<Settings> settings = promise.get_future().share();
~~~

get_future() получает future, связанный с promise. share() передаёт его
состояние в shared_future. Исходный future после share() уже не содержит
этого состояния; здесь временный future сразу уничтожается.

Лямбда захватывает settings по значению. Каждый поток получает собственную
копию shared_future, но все копии ссылаются на одно общее состояние.
Копируется средство доступа к результату, а не отдельная загрузка настроек.

~~~cpp
const Settings& received = settings.get();
~~~

get() ждёт готовности, если производитель ещё не вызвал set_value().
Если результат уже опубликован, get() возвращается без ожидания его подготовки.
Уведомления вручную не нужны: promise и future согласуют готовность сами.

promise.set_value(Settings{4, "localhost"}) публикует настройки один раз.
Все три работника получают localhost и maxConnections == 4.
В main get() вызывается ещё два раза:

~~~text
Main get #1: 4
Main get #2: 4
~~~

У обычного std::future вызов get() потребляет состояние, поэтому повторно
получать результат через тот же future нельзя. У shared_future get() можно
вызывать многократно. Для Settings он возвращает const Settings&;
ссылка действительна, пока общее состояние удерживается владельцами.

В примере каждый поток использует свою копию shared_future.
Полученные настройки только читаются. shared_future не делает произвольное
изменение объекта результата потокобезопасным.
outputMtx нужен для цельных строк консоли.

## main2.cpp: одно исключение для всех

Вместо set_value() производитель вызывает:

~~~cpp
promise.set_exception(
    std::make_exception_ptr(std::runtime_error("Configuration unavailable")));
~~~

Каждый get() повторно выбрасывает сохранённое исключение.
Каждый работник обрабатывает его своим catch:

~~~text
Workers that received the exception: 3
~~~

Сами строки Worker могут идти в любом порядке.
Исключение не исчезает после первого потребителя.

## Сборка и запуск

Откройте main.cpp или main2.cpp и нажмите F5 либо Ctrl+F5.
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

Для исключения замените main.cpp/main на main2.cpp/main2.
После добавления исходников обновите IntelliSense через задачу
C/C++: Update IntelliSense.

[shared_future в проекте стандарта](https://eel.is/c++draft/futures.shared.future).
[Все бонусы](../README.md).
