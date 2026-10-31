# Сети на C++: Windows и Linux

Дополнительное направление вне исходного курса. Все уроки используют C++17.
Начните с основ языка, RAII и обработки исключений. Для уроков 09–10 полезны
[многопоточность](../../multithreading/README.md) и condition_variable.

## Порядок изучения

1. [Адреса и порты](lesson-01-addresses/) — localhost, IPv4/IPv6, getaddrinfo и порядок байтов.
2. [TCP echo](lesson-02-tcp-echo/) — клиент, сервер, connect, bind, listen и accept.
3. [Границы TCP-сообщений](lesson-03-tcp-framing/) — префикс длины, частичные send/recv и двоичные данные.
4. [UDP echo](lesson-04-udp-echo/) — sendto/recvfrom и отдельные датаграммы.
5. [Таймауты и ошибки](lesson-05-timeouts/) — неблокирующий сокет, select, SO_ERROR и закрытие соединения.
6. [HTTP GET](lesson-06-http-get/) — строка запроса, заголовки, тело и статус.
7. [HTTP POST и JSON](lesson-07-http-post-json/) — передача настроек, Content-Type и проверка тела.
8. [API в стиле REST](lesson-08-rest-api/) — POST/GET/PUT/DELETE и жизненный цикл ресурса.
9. [Несколько клиентов](lesson-09-multi-client/) — независимые соединения и параллельные обработчики.
10. [Фоновая отправка](lesson-10-background-sender/) — latest value, mutex, condition_variable и завершение.
11. [HTTPS](lesson-11-https/) — TLS, доверенный CA и проверка имени сервера через libcurl.
12. [IPv6](lesson-12-ipv6/) — соединение через ::1 и выбор кандидата из getaddrinfo().
13. [Переподключение](lesson-13-reconnect/) — ограниченные повторы, backoff и отмена.
14. [Heartbeat](lesson-14-heartbeat/) — прикладные PING/PONG и таймаут ответа.
15. [ACK и request_id](lesson-15-request-ack/) — потерянный ответ, повтор команды и кэш результата.
16. [Передача файла](lesson-16-file-transfer/) — блоки, прогресс, CRC32 и подтверждение записи.
17. [UDP discovery](lesson-17-udp-discovery/) — unicast, broadcast, multicast и фильтрация повторов.
18. [Boost.Asio](lesson-18-asio/) — асинхронные операции, буферы и таймеры сессий.
19. [WebSocket](lesson-19-websocket/) — серверные события и двусторонний обмен с Boost.Beast.

Уроки используют самостоятельные примеры: echo, передачу сообщений,
HTTP API и фоновую отправку данных.

## Что относится к какому уровню

IP задаёт адресацию; TCP передаёт упорядоченный поток байтов, а UDP — датаграммы.
Сокет — программный интерфейс работы с сетью.
HTTP описывает запросы и ответы, в том числе методы GET, POST, PUT и DELETE.
REST — архитектурный стиль; использование GET и POST само по себе ещё не означает
выполнение всех ограничений REST. Урок 08 демонстрирует ресурсный HTTP API,
без полного набора механизмов REST, например гипермедиа.
HTTPS использует HTTP поверх защищённого соединения TLS.

По умолчанию примеры слушают loopback 127.0.0.1, а урок 12 — IPv6 ::1.
Loopback не открывает сервер другим компьютерам.
В уроке 17 broadcast/multicast включаются отдельными аргументами;
эти режимы могут использовать локальную сеть и слушать 0.0.0.0.
Для HTTP-клиентов можно явно передать URL, для HTTPS по умолчанию используется
https://example.com/; остальные стандартные запуски не требуют Интернета.

## Windows

Используются MSYS2 MinGW64, g++ и GDB, как в основном проекте.
WinSock инициализируется через WSAStartup(), сокет имеет тип SOCKET,
закрывается через closesocket(). Сборка добавляет -lws2_32.

HTTP/HTTPS-клиенты требуют libcurl от того же окружения MinGW64.
Если она ещё не установлена, в терминале MSYS2 выполните:

~~~bash
pacman -S --needed mingw-w64-x86_64-curl
~~~

C:/msys64/mingw64/bin должен быть в PATH для загрузки DLL.
При стандартной установке проекта дополнительных путей заголовков не требуется.
Не смешивайте библиотеки MinGW64 и UCRT64.
[Пакет libcurl в MSYS2](https://packages.msys2.org/packages/mingw-w64-x86_64-curl).

Уроки 18–19 дополнительно требуют заголовки Boost.Asio и Boost.Beast:

~~~bash
pacman -S --needed mingw-w64-x86_64-boost
~~~

[Пакет Boost в MSYS2](https://packages.msys2.org/packages/mingw-w64-x86_64-boost).
Отдельная standalone Asio не нужна: оба урока используют Boost.Asio.

## Linux

Используются POSIX-сокеты: файловый дескриптор int, close(), fcntl().
На Debian/Ubuntu зависимости можно установить так:

~~~bash
sudo apt-get install g++ gdb libcurl4-openssl-dev python3 openssl
~~~

libcurl требуется для HTTP/HTTPS-клиентов. Python и OpenSSL нужны
для локальных интеграционных проверок, но не для обычного запуска TCP/UDP.
Для уроков 18–19 установите также libboost-dev:

~~~bash
sudo apt-get install libboost-dev
~~~

## Сборка и запуск

Команды выполняются из корня cpp-simplecode-lessons.
Каждый .cpp — отдельная программа; server.cpp и client.cpp не связываются вместе.
Пример на Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-02-tcp-echo/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-02-tcp-echo/client.cpp
~~~

В первом терминале:

~~~bash
./build/bonus/networking/lesson-02-tcp-echo/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-02-tcp-echo/client
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-02-tcp-echo/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-02-tcp-echo/client.cpp
~~~

В первом терминале:

~~~powershell
& .\build\bonus\networking\lesson-02-tcp-echo\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-02-tcp-echo\client.exe
~~~

В README каждого урока приведены его команды.
Серверы конечны: обычно один клиент/запрос; у API пять запросов,
у многопользовательского примера и Asio три клиента. Ожидание подключения
ограничено 15 секундами: при таймауте перезапустите сервер.
Урок 13 дополнительно показывает запуск клиента раньше готовности сервера.

Для TCP/UDP можно передать порт первым аргументом обеим программам.
Порт 0 у сервера выбирает свободный порт автоматически и печатает его.
HTTP-клиентам передаётся целый URL, API-клиенту — базовый URL без завершающего /.
В уроке 12 клиент принимает имя после порта, а discovery — режим и интерфейс.
В остальных нативных TCP-примерах адрес сервера остаётся loopback.

## VS Code

Откройте корень проекта или папку конкретного урока.
Обновите IntelliSense задачей C/C++: Update IntelliSense.
Активный .cpp можно собрать и запустить через F5/Ctrl+F5.
Сначала должен быть запущен сервер, затем клиент.

При открытии отдельного урока с парой программ доступны задачи:

- Networking: Run server — соберёт server.cpp и запустит в своём терминале.
- Networking: Run client — соберёт client.cpp и запустит в другом терминале.

Запустите первую задачу, дождитесь Listening, затем вторую.
Не задавайте зависимость «дождаться завершения сервера перед клиентом»:
сервер сам ждёт клиента. Автоматического одновременного старта здесь нет.
Для F5 удобно оставить сервер работающим в терминале, а отлаживать client.cpp.
Сами папки bonus/ и networking/ не являются отдельными рабочими областями VS Code.

## Общий код

- [common/net.hpp](common/net.hpp) — Runtime, RAII Socket, различия WinSock/POSIX,
  неблокирующий режим, select, дедлайны, sendAll и чтение сообщений.
- [common/http.hpp](common/http.hpp) — ограниченный локальный HTTP/1.x-сервер.
  Один запрос на соединение, Content-Length, заголовки до 8 КиБ, тело до 4 КиБ.
  Keep-alive, chunked и TLS-сервер в нём не реализованы.
- [common/curl_client.hpp](common/curl_client.hpp) — HTTP/HTTPS-клиент libcurl,
  таймауты, RAII ресурсов и ограничение ответа 64 КиБ.
- [common/resolved_address.hpp](common/resolved_address.hpp) — попытки соединения по IPv4/IPv6-кандидатам.
- [common/crc32.hpp](common/crc32.hpp) — потоковое вычисление CRC-32/ISO-HDLC.
- [common/boost_net.hpp](common/boost_net.hpp) — заголовки и настройка Boost.Asio для Windows/Linux.

Общий код вынесен, чтобы в уроках были видны действия клиента и сервера,
а не повторяющиеся платформенные ветки. Его функции — часть учебного материала:
открывайте реализацию по мере изучения соответствующего вызова.
JSON-парсер понимает только объект с одним целочисленным полем value.
Для произвольного JSON и полноценного HTTP-сервера нужны соответствующие библиотеки.

link-libraries.txt рядом с исходниками задаёт нужные библиотеки:
ws2_32/mswsock на Windows и curl для HTTP/HTTPS. Общие скрипты читают этот файл.
Для компиляции без линковки IntelliSense эти -l-флаги не нужны.

## Локальная проверка

Сначала соберите все .cpp. На Linux из корня:

~~~bash
for source in bonus/networking/lesson-*/*.cpp; do bash scripts/build-linux.sh "$source" || break; done
python3 bonus/networking/tests/smoke.py
~~~

На Windows из PowerShell:

~~~powershell
Get-ChildItem bonus\networking\lesson-*\*.cpp | ForEach-Object {
    & C:\msys64\usr\bin\bash.exe scripts/build-windows.sh $_.FullName
    if ($LASTEXITCODE -ne 0) { throw "Build failed" }
}
python bonus/networking/tests/smoke.py
~~~

Проверка обращается только к loopback. Она проверяет echo, кадры с нулевым байтом,
таймаут, недоступный порт, HTTP-ошибки, API, параллельных клиентов и фоновую отправку.
Для HTTPS создаётся временный самоподписанный сертификат: проверяются доверенный CA,
отсутствие доверия и несовпадение имени. Нужен openssl в PATH.
Явный параметр --skip-tls пропускает только эти проверки.

После сборки уроков 12–19 выполните расширенную проверку:

~~~bash
python3 bonus/networking/tests/smoke_extended.py
~~~

На Windows используйте python вместо python3. Она проверяет IPv6 loopback,
переподключение и отмену, heartbeat, потерю ACK, файлы, discovery, Asio и WebSocket.
Данные передачи файлов создаются во временном каталоге внутри build/.
Файловые проверки включают пустой файл, известную CRC32, ошибочную сумму,
недопустимое имя и предел размера.

Дополнительно можно проверить multicast именно через loopback:

~~~bash
python3 bonus/networking/tests/smoke_extended.py --multicast
~~~

LAN broadcast эти тесты не отправляют. Он проверяется вручную
только при явном выборе соответствующего режима в уроке 17.

## Справочные материалы

- [WinSock: инициализация](https://learn.microsoft.com/en-us/windows/win32/winsock/initializing-winsock).
- [WinSock: неблокирующий ввод-вывод](https://learn.microsoft.com/en-us/windows/win32/winsock/nonblocking-i-o-2).
- [TCP — RFC 9293](https://www.rfc-editor.org/rfc/rfc9293.html).
- [HTTP semantics — RFC 9110](https://www.rfc-editor.org/rfc/rfc9110.html).
- [HTTP/1.1 — RFC 9112](https://www.rfc-editor.org/rfc/rfc9112.html).
- [libcurl](https://curl.se/libcurl/c/).
- [REST: описание автора](https://ics.uci.edu/~fielding/pubs/dissertation/rest_arch_style.htm).

[Дополнительные направления](../README.md). [Все уроки](../../LESSONS.md).
