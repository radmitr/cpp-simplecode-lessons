# 05. UDP echo и датаграммы

## Версия C++

`std::chrono`, `auto`, лямбды — **C++11**.
`std::string`, `std::exception`, `std::runtime_error`, `std::size_t` — **C++98**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.
WinSock/POSIX-сокеты — платформенные API, не часть стандарта C++.

## Что изучаем

`SOCK_DGRAM` создаёт UDP-сокет. Сервер привязывает его к `loopback`-порту,
`recvfrom()` получает датаграмму и адрес отправителя, `sendto()` отправляет ответ.
У UDP в этом примере нет `listen()`, `accept()` и предварительного TCP-подключения.

Windows: MinGW64; Linux: POSIX.

## Примеры

- [client.cpp](client.cpp).
- [server.cpp](server.cpp).

Сервер и клиент — две отдельные программы. Нужны обе: сначала сервер
в одном терминале, затем клиент в другом. Каждый исходник собирается отдельно.

## Как это работает

Клиент отправляет Hello over UDP и ждёт ответ с тем же содержимым.
Он также проверяет адрес и порт отправителя. Ожидаемый вывод:

~~~text
Datagram echo: Hello over UDP
~~~

У UDP сохраняются границы датаграмм, но нет гарантий доставки, порядка
или отсутствия дубликатов. Успешный `sendto()` означает принятие данных локальной
системой, а не подтверждение доставки серверу. В этом примере подтверждением
на уровне приложения является echo. Автоматических повторов здесь нет.

Нулевая длина UDP-датаграммы допустима; `recvfrom() == 0` не означает закрытие
UDP-соединения. В отличие от TCP, такого потока-соединения здесь вообще нет.

Учебный буфер равен 1024 байтам, отправляемое сообщение намного меньше.
Для слишком большой датаграммы поведение включает обрезание или ошибку
в зависимости от API и ОС: нельзя считать этот пример передачей любого файла.

## Сборка и запуск

[Запуск в VS Code](../../../README.md#сборка-и-запуск-в-vs-code).

Порт по умолчанию: 42004. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh additions/networking/05-udp-echo/server.cpp
bash scripts/build-linux.sh additions/networking/05-udp-echo/client.cpp
~~~

Первый терминал:

~~~bash
./build/additions/networking/05-udp-echo/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/additions/networking/05-udp-echo/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/05-udp-echo/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/05-udp-echo/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\additions\networking\05-udp-echo\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\additions\networking\05-udp-echo\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на `client.cpp`.
Для запуска без отладки используйте Ctrl+F5.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).

## Связанные темы и источники

[Версии C++](../../../docs/cpp-versions.md) · [Как читать справочники](../../../docs/references.md).
