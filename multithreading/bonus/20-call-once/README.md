# 20. std::call_once и std::once_flag

C++17. Три потока используют общие настройки, которые нужно подготовить
только один раз. Каждый вызывает одну и ту же конструкцию:

~~~cpp
std::call_once(initFlag, initialize);
~~~

initFlag хранит состояние однократной инициализации. Один из потоков выполняет
initialize(), а другие вызовы с этим же флагом ожидают успешного завершения.
После этого они возвращаются, не вызывая initialize() повторно.
Какой поток окажется инициализатором, заранее неизвестно.

## main.cpp: успешная инициализация

initialize() записывает settings и увеличивает initializationCount.
После call_once() все работники могут читать подготовленную строку:
результаты успешной инициализации видны другим вызовам с тем же initFlag.
Отдельный outputMtx защищает только печать целых сообщений.

Порядок строк Worker неизвестен, но итог должен быть таким:

~~~text
Successful initializations: 1
~~~

call_once() не защищает последующие изменения settings. Если после
инициализации кто-то начнёт менять строку, потребуется отдельная синхронизация.
В этом примере работники только читают её.

## main2.cpp: повторная попытка после исключения

Этот вариант запускайте на Linux. При проверке текущего MinGW/libstdc++
повторный call_once() после исключения завис внутри реализации pthread_once.
Поэтому при сборке MinGW/libstdc++ main2.cpp выводит пояснение и завершает
работу, не выполняя этот эксперимент. main.cpp на Windows работает.
Это ограничение проверенного инструментария, а не требуемое поведение C++.
[Примечания libstdc++ о поддержке исключений call_once](https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html).

Первая попытка намеренно бросает std::runtime_error. Исключение передаётся
тому, кто вызвал call_once(), и обрабатывается в catch.
Флаг ещё не отмечен как успешно выполненный: следующий вызов снова запускает
initialize(). Вторая попытка завершается успешно, последующие её не повторяют:

~~~text
First attempt: Configuration unavailable
Worker 1: server=localhost
Worker 2: server=localhost
Initialization attempts: 2
~~~

Номера работников могут поменяться местами. call_once() сам не перезапускает
функцию в цикле: для следующей попытки нужен следующий вызов call_once().
Отката частично выполненных действий после исключения тоже нет.

once_flag нельзя копировать или сбросить для новой инициализации.
Для простого локального ресурса также существует потокобезопасная
инициализация локальной static-переменной, начиная с C++11.

## Сборка и запуск

Откройте main.cpp и нажмите F5 либо Ctrl+F5; main2.cpp выполняет
эксперимент с исключением только вне MinGW/libstdc++.
Из корня репозитория на Linux:

~~~bash
bash scripts/build-linux.sh multithreading/bonus/20-call-once/main.cpp
./build/multithreading/bonus/20-call-once/main
~~~

На Windows из MSYS2 Bash:

~~~bash
bash scripts/build-windows.sh multithreading/bonus/20-call-once/main.cpp
./build/multithreading/bonus/20-call-once/main.exe
~~~

Для второго варианта замените main.cpp/main на main2.cpp/main2.
После добавления исходников обновите IntelliSense через задачу
C/C++: Update IntelliSense.

[call_once в проекте стандарта](https://eel.is/c++draft/thread.once.callonce).
[Все бонусы](../README.md).
