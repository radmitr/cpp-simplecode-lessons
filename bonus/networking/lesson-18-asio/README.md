# 18. Асинхронный TCP-сервер с Boost.Asio

C++17. Windows: MinGW64; Linux: POSIX. Нужны заголовки Boost.

Урок использует Boost.Asio. Это вариант Asio в составе Boost; он также
нужен следующему уроку с Boost.Beast. Отдельная standalone Asio не требуется.

Клиент создаёт три соединения, как в уроке 09.
Сервер обрабатывает их через async_accept(), async_read_until()
и async_write(). io_context::run() выполняется только в одном потоке.

Это не три одновременно выполняющихся обработчика:
готовые обработчики вызываются последовательно, а ожидания сети перекрываются.
Пока одна операция ждёт данные, io_context может обрабатывать другое соединение.
Долгая блокирующая работа внутри обработчика задержит остальные.

Каждый Session владеет своим сокетом, входным буфером, строкой ответа и таймером.
shared_ptr, захваченный обработчиками, сохраняет Session до их завершения.
Нельзя передавать в async_write() буфер локальной строки,
которая уничтожится раньше окончания отправки.

Таймер сессии ограничивает чтение и отправку тремя секундами.
Общий таймер приёма даёт 15 секунд на три подключения.
При завершении Session таймер отменяется, сокет закрывается.
Флаг finished_ предотвращает повторное завершение из конкурирующих событий
таймера и сетевой операции. Обработчики отменённых операций тоже будут вызваны
и проверяют свой код ошибки.

Ожидаемый вывод клиента:

~~~text
Async echo verified: 3 clients
~~~

Сервер печатает Async clients: 3 и строки обработанных сообщений
в порядке готовности. После трёх соединений он заканчивает принимать новые
и дожидается завершения сессий. Исключения и ошибки не создают бесконечный сервер.

[Учебник Boost.Asio](https://www.boost.org/doc/libs/latest/doc/html/boost_asio/tutorial.html).

## Сборка и запуск

Команды выполняются из корня проекта. Порт по умолчанию — 42018.
Сначала соберите обе программы.

Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-18-asio/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-18-asio/client.cpp
~~~

В первом терминале:

~~~bash
./build/bonus/networking/lesson-18-asio/server
~~~

Во втором терминале после Listening:

~~~bash
./build/bonus/networking/lesson-18-asio/client
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-18-asio/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-18-asio/client.cpp
~~~

В первом терминале:

~~~powershell
& .\build\bonus\networking\lesson-18-asio\server.exe
~~~

Во втором терминале после Listening:

~~~powershell
& .\build\bonus\networking\lesson-18-asio\client.exe
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
