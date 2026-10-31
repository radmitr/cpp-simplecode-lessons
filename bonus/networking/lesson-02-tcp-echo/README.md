# 02. TCP echo: клиент и сервер

C++17. Windows: MinGW64; Linux: POSIX.

Сервер принимает одно соединение и возвращает полученную строку.
Клиент отправляет Hello over TCP и проверяет, что ответ совпал.

Сервер: socket(SOCK_STREAM) -> bind(127.0.0.1) -> listen() -> accept().
listen() переводит сокет в режим ожидания подключений. accept() создаёт
новый сокет конкретного клиента; слушающий сокет остаётся отдельным.
Клиент: socket() -> connect() -> send() -> recv().

TCP — поток байтов. Даже здесь receiveLine() читает до выбранной границы
сообщения, символа \n, а sendAll() проверяет, сколько байтов отправлено.
Один send() не означает один recv(). Следующий урок разбирает это подробнее.

net::Socket владеет дескриптором и закрывает его в деструкторе, в том числе
при исключении. Копирование запрещено, перемещение передаёт владение.
На Windows используется SOCKET/closesocket(), на Linux int/close().
Изучите эти классы в common/net.hpp: создание и освобождение сокета
не должны теряться при раннем return или ошибке.

Ожидаемый вывод клиента:

~~~text
Echo: Hello over TCP
~~~

Сервер завершится после одной строки. Для следующего запуска клиента
нужно снова запустить сервер. EOF до символа \n считается неполным сообщением.

## Сборка и запуск

Порт по умолчанию: 42002. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-02-tcp-echo/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-02-tcp-echo/client.cpp
~~~

Первый терминал:

~~~bash
./build/bonus/networking/lesson-02-tcp-echo/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-02-tcp-echo/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-02-tcp-echo/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-02-tcp-echo/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\bonus\networking\lesson-02-tcp-echo\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-02-tcp-echo\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на client.cpp.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
