# 19. WebSocket: сообщения от сервера

C++17. Windows: MinGW64; Linux: POSIX. Нужны заголовки Boost.

Используются Boost.Asio и Boost.Beast.
WebSocket начинается с HTTP Upgrade handshake, затем использует своё
кадрирование сообщений поверх TCP. Это не просто строки с \n.

Сервер после handshake сам отправляет tick 1, tick 2 и tick 3
с интервалом около 100 мс. Для каждого сообщения новый HTTP-запрос не нужен.
Клиент читает три события, отправляет ACK 3 и принимает нормальное закрытие:

~~~text
Event: tick 1
Event: tick 2
Event: tick 3
WebSocket complete: 3 events
~~~

Beast выполняет handshake, собирает сообщения из кадров, обрабатывает
маскирование клиентских кадров и WebSocket close handshake.
Приложение работает с готовыми текстовыми сообщениями.

Операции асинхронны. На каждом соединении записи выполняются последовательно:
следующая начинается после окончания предыдущей.
Буферы message_ и ack_ — поля объектов, которые существуют до завершения операций.
Максимальный размер принимаемого сообщения — 4096 байтов.

На стороне сервера handshake ограничен двумя секундами;
общая сессия — пятью секундами. Прикреплённые к shared_ptr обработчики
поддерживают время жизни объекта. По завершении таймеры отменяются,
а отменённые обработчики безопасно заканчивают работу.

Пример использует ws:// без TLS и принимает один клиент.
Для шифрования WebSocket использует wss://; это потребует TLS-слоя и сертификата,
как в уроке HTTPS. WSS в этот урок не включён.
Путь клиента — /events; учебный сервер не реализует отдельный маршрутизатор путей.

Независимая локальная проверка на Python проверяет RFC-handshake,
серверные немаскированные кадры, клиентский маскированный ACK и закрытие с кодом 1000.
[Протокол WebSocket](https://www.rfc-editor.org/rfc/rfc6455.html).
[WebSocket в Boost.Beast](https://www.boost.org/doc/libs/latest/libs/beast/doc/html/beast/quick_start/websocket_client.html).

## Сборка и запуск

Команды выполняются из корня проекта. Порт по умолчанию — 42019.
Сначала соберите обе программы.

Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-19-websocket/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-19-websocket/client.cpp
~~~

В первом терминале:

~~~bash
./build/bonus/networking/lesson-19-websocket/server
~~~

Во втором терминале после Listening:

~~~bash
./build/bonus/networking/lesson-19-websocket/client
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-19-websocket/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-19-websocket/client.cpp
~~~

В первом терминале:

~~~powershell
& .\build\bonus\networking\lesson-19-websocket\server.exe
~~~

Во втором терминале после Listening:

~~~powershell
& .\build\bonus\networking\lesson-19-websocket\client.exe
~~~

Windows: пакет mingw-w64-x86_64-boost; Debian/Ubuntu: libboost-dev.
Отдельная линковка с boost_system для используемого header-only режима
актуального Boost не требуется. На Windows подключаются ws2_32 и mswsock.

При открытии папки урока в VS Code используйте Networking: Run server,
затем Networking: Run client. Задачи соберут нужные исходники и запустят их
в разных терминалах. Для отладки клиента оставьте сервер в терминале
и нажмите F5 на client.cpp. Дополнительные аргументы можно передавать из терминала.
После добавления исходников обновите C/C++: Update IntelliSense.

[Зависимости, общий код и все сетевые уроки](../README.md).
