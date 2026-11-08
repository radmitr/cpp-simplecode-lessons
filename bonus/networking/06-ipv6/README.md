# 06. IPv6-клиент и сервер

## Версия C++

`std::chrono`, `auto` — **C++11**.
`std::string`, `std::exception`, `std::runtime_error` — **C++98**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.
WinSock/POSIX-сокеты — платформенные API, не часть стандарта C++.

## Что изучаем

Сервер создаёт сокет `AF_INET6`, привязывает его к ::1 и принимает одно соединение.
IPV6_V6ONLY явно отделяет его от IPv4. Клиент по умолчанию обращается к localhost.

Windows: MinGW64; Linux: POSIX.

## Примеры

- [client.cpp](client.cpp).
- [server.cpp](server.cpp).

Сервер и клиент — две отдельные программы. Нужны обе: сначала сервер
в одном терминале, затем клиент в другом. Каждый исходник собирается отдельно.

## Как это работает

`getaddrinfo(AF_UNSPEC)` возвращает кандидатов IPv4 и IPv6 в порядке ОС.
`net::connectHost()` пробует их по очереди до успешного подключения.
Для каждого адреса создаётся свой сокет нужного семейства.
Одна неудачная попытка не означает, что недоступны остальные адреса.

Ожидаемый вывод клиента:

~~~text
IPv6 echo: Hello over IPv6
~~~

Клиенту можно передать имя после порта:

~~~text
client 42012 ::1
client 42012 localhost
~~~

Если `localhost` разрешается только в IPv4, передайте `::1` явно:
сервер этого урока слушает только IPv6. Наличие IPv6 loopback само по себе
не гарантирует, что имя `localhost` связано с `::1` в настройках ОС.

В IPv6 адрес и порт обычно записывают как [::1]:42012: скобки отделяют
двоеточия адреса от двоеточия перед портом. В `getaddrinfo()` передаётся ::1
без квадратных скобок.

Дедлайн относится к попыткам подключения. Синхронный `getaddrinfo()` сам по себе
им не прерывается. Для внешнего DNS нужен отдельный подход к таймауту разрешения.
Пример требует включённого IPv6 loopback; отключённый IPv6 даст ошибку ОС.

## Сборка и запуск

[Запуск в VS Code](../../../README.md#сборка-и-запуск-в-vs-code).

Команды выполняются из корня проекта. Порт по умолчанию — 42012.
Сначала соберите обе программы.

Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/06-ipv6/server.cpp
bash scripts/build-linux.sh bonus/networking/06-ipv6/client.cpp
~~~

В первом терминале:

~~~bash
./build/bonus/networking/06-ipv6/server
~~~

Во втором терминале после Listening:

~~~bash
./build/bonus/networking/06-ipv6/client
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/06-ipv6/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/06-ipv6/client.cpp
~~~

В первом терминале:

~~~powershell
& .\build\bonus\networking\06-ipv6\server.exe
~~~

Во втором терминале после Listening:

~~~powershell
& .\build\bonus\networking\06-ipv6\client.exe
~~~

При открытии папки урока в VS Code используйте Networking: Run server,
затем Networking: Run `client`. Задачи соберут нужные исходники и запустят их
в разных терминалах. Для отладки клиента оставьте сервер в терминале
и нажмите F5 на `client.cpp`. Дополнительные аргументы можно передавать из терминала.
После добавления исходников обновите C/C++: Update IntelliSense.
Для запуска без отладки используйте Ctrl+F5.

[Зависимости, общий код и все сетевые уроки](../README.md).

## Связанные темы и источники

[Версии C++](../../../docs/cpp-versions.md) · [Как читать справочники](../../../docs/references.md).
