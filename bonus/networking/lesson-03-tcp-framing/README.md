# 03. Границы сообщений в TCP

C++17. Windows: MinGW64; Linux: POSIX.

TCP не хранит границы вызовов send(). Несколько отправок могут быть прочитаны
одним recv(), а одна отправка — несколькими. Прикладной протокол сам определяет,
где заканчивается сообщение.

Здесь перед телом передаются четыре байта длины uint32_t в сетевом порядке.
sendFrame() формирует заголовок через htonl(), затем добавляет ровно тело.
receiveFrame() сначала читает ровно четыре байта через receiveExact(),
преобразует длину через ntohl() и читает указанное количество байтов.

Заголовок копируется в число через memcpy: нельзя просто разыменовать
указатель uint32_t* на произвольно выровненные байты строки.

Клиент проверяет три сообщения:

~~~text
Verified frame: 5 bytes
Verified frame: 0 bytes
Verified frame: 3 bytes
~~~

Последнее — A, нулевой байт, B. Это три байта, хотя C-строка закончилась бы
на первом \0. Пустое тело тоже допустимо: заголовок с длиной 0 является кадром,
а TCP recv() == 0 означает закрытие соединения.

Для наглядности sendFrame() ограничивает каждый вызов send() тремя байтами.
Это искусственное разбиение на стороне приложения, а не обещание конкретных
размеров TCP-пакетов или recv(). sendAll() повторяет отправку оставшихся байтов.

Максимальная длина кадра — 65536 байтов. Размер проверяется до выделения тела.
Один общий deadline используется во всём чтении кадра: очередной полученный
байт не начинает таймаут заново.

## Сборка и запуск

Порт по умолчанию: 42003. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-03-tcp-framing/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-03-tcp-framing/client.cpp
~~~

Первый терминал:

~~~bash
./build/bonus/networking/lesson-03-tcp-framing/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-03-tcp-framing/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-03-tcp-framing/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-03-tcp-framing/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\bonus\networking\lesson-03-tcp-framing\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-03-tcp-framing\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на client.cpp.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
