# 12. IPv6-клиент и сервер

C++17. Windows: MinGW64; Linux: POSIX.

Сервер создаёт сокет AF_INET6, привязывает его к ::1 и принимает одно соединение.
IPV6_V6ONLY явно отделяет его от IPv4. Клиент по умолчанию обращается к localhost.

getaddrinfo(AF_UNSPEC) возвращает кандидатов IPv4 и IPv6 в порядке ОС.
net::connectHost() пробует их по очереди до успешного подключения.
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

В IPv6 адрес и порт обычно записывают как [::1]:42012: скобки отделяют
двоеточия адреса от двоеточия перед портом. В getaddrinfo() передаётся ::1
без квадратных скобок.

Дедлайн относится к попыткам подключения. Синхронный getaddrinfo() сам по себе
им не прерывается. Для внешнего DNS нужен отдельный подход к таймауту разрешения.
Пример требует включённого IPv6 loopback; отключённый IPv6 даст ошибку ОС.

## Сборка и запуск

Команды выполняются из корня проекта. Порт по умолчанию — 42012.
Сначала соберите обе программы.

Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-12-ipv6/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-12-ipv6/client.cpp
~~~

В первом терминале:

~~~bash
./build/bonus/networking/lesson-12-ipv6/server
~~~

Во втором терминале после Listening:

~~~bash
./build/bonus/networking/lesson-12-ipv6/client
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-12-ipv6/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-12-ipv6/client.cpp
~~~

В первом терминале:

~~~powershell
& .\build\bonus\networking\lesson-12-ipv6\server.exe
~~~

Во втором терминале после Listening:

~~~powershell
& .\build\bonus\networking\lesson-12-ipv6\client.exe
~~~

При открытии папки урока в VS Code используйте Networking: Run server,
затем Networking: Run client. Задачи соберут нужные исходники и запустят их
в разных терминалах. Для отладки клиента оставьте сервер в терминале
и нажмите F5 на client.cpp. Дополнительные аргументы можно передавать из терминала.
После добавления исходников обновите C/C++: Update IntelliSense.

[Зависимости, общий код и все сетевые уроки](../README.md).
