# Сети на C++: Windows и Linux

Дополнительное направление вне исходного курса. Все уроки используют C++17.
Начните с основ языка, RAII и обработки исключений. Для уроков [«08. Параллельная обработка нескольких клиентов»](08-multi-client/README.md) — [«09. Фоновая отправка последнего значения»](09-background-sender/README.md) полезны
[многопоточность](../../multithreading/README.md) и `condition_variable`.

## Уроки

- [01. Адреса, DNS и порядок байтов](01-addresses/README.md) — `c++17`.
- [02. Подсети, выбор маршрута и разрешение имён](02-subnets-and-routing/README.md) — `c++17`.
- [03. TCP echo: клиент и сервер](03-tcp-echo/README.md) — `c++17`.
- [04. Границы сообщений в TCP](04-tcp-framing/README.md) — `c++17`.
- [05. UDP echo и датаграммы](05-udp-echo/README.md) — `c++17`.
- [06. Неблокирующие сокеты, таймауты и ошибки](06-timeouts/README.md) — `c++17`.
- [07. IPv6-клиент и сервер](07-ipv6/README.md) — `c++17`.
- [08. Параллельная обработка нескольких клиентов](08-multi-client/README.md) — `c++17`.
- [09. Фоновая отправка последнего значения](09-background-sender/README.md) — `c++17`.
- [10. Переподключение, backoff и отмена](10-reconnect/README.md) — `c++17`.
- [11. Heartbeat: PING/PONG](11-heartbeat/README.md) — `c++17`.
- [12. ACK, request_id и защита от повторного выполнения](12-request-ack/README.md) — `c++17`.
- [13. Передача файла блоками и CRC32](13-file-transfer/README.md) — `c++17`.
- [14. Обнаружение устройств через UDP](14-udp-discovery/README.md) — `c++17`.
- [15. HTTP GET и ответ сервера](15-http-get/README.md) — `c++17`.
- [16. HTTP POST с JSON](16-http-post-json/README.md) — `c++17`.
- [17. Ресурсный HTTP API](17-rest-api/README.md) — `c++17`.
- [18. HTTPS и проверка сертификата](18-https/README.md) — `c++17`.
- [19. Аутентификация, права доступа и mTLS](19-auth-and-mtls/README.md) — `c++17`.
- [20. HTTP/2 и HTTP/3 через libcurl](20-http-versions/README.md) — `c++17`.
- [21. Мультиплексирование HTTP и границы QUIC](21-http-multiplexing/README.md) — `c++17`.
- [22. Асинхронный TCP-сервер с `Boost.Asio`](22-asio/README.md) — `c++17`.
- [23. WebSocket: сообщения от сервера](23-websocket/README.md) — `c++17`.
- [24. WSS: WebSocket поверх TLS](24-wss/README.md) — `c++17`.
- [25. Многопоточный Asio и strand](25-asio-strand/README.md) — `c++17`.
- [26. Ограничение нагрузки и обратное давление](26-backpressure-and-rate-limits/README.md) — `c++17`.
- [27. Выбор сервера и отказоустойчивые повторы](27-load-balancing/README.md) — `c++17`.
- [28. MQTT: публикация и подписка через брокер](28-mqtt/README.md) — `c++17`.
- [29. MQTT: QoS, подтверждения и дубликаты](29-mqtt-delivery/README.md) — `c++17`.
- [30. Некорректные данные, фрагментация и диагностика](30-protocol-testing/README.md) — `c++17`.
- [31. Итоговый проект: чат с переподключением и heartbeat](31-chat/README.md) — `c++17`.

## Дополнительный справочный блок

После транспортных и HTTP-примеров разберите mTLS и роли, curl multi, ограничение
нагрузки, балансировку, MQTT QoS и проверку фрагментации. Эти темы встроены
в каталог по зависимостям; чат остаётся итоговым проектом. Модели маршрутизации
и балансировки не изменяют сеть ОС и не являются готовым прокси.

Проверить новые примеры одной командой из корня:

```bash
python3 additions/networking/tests/check-reference.py
```

Runner сам собирает нужные программы и использует только loopback, Python stdlib
и `openssl` из `PATH`. Он подготавливает временные сертификаты, проверяет mTLS,
роли HTTP, curl multi на HTTP/1.1 и QoS 1 через ограниченный fixture. Настоящее
HTTP/2–3 и полноценный MQTT-брокер проверяются отдельно существующей расширенной
проверкой; её внешние зависимости описаны в [инструкции](tests/README.md).

Раздел не исчерпывает сетевое программирование: реализация QUIC, MQTT 5,
эксплуатация NAT/firewall, распределённая координация и промышленная инфраструктура
сертификатов остаются самостоятельными направлениями. Границы каждого примера
явно указаны в его README.

## Что относится к какому уровню

IP задаёт адресацию; TCP передаёт упорядоченный поток байтов, а UDP — датаграммы.
Сокет — программный интерфейс работы с сетью.
HTTP описывает запросы и ответы, в том числе методы GET, POST, PUT и `DELETE`.
REST — архитектурный стиль; использование GET и POST само по себе ещё не означает
выполнение всех ограничений REST. Урок [«17. Ресурсный HTTP API»](17-rest-api/README.md) демонстрирует ресурсный HTTP API,
без полного набора механизмов REST, например гипермедиа.
HTTPS использует HTTP поверх защищённого соединения TLS.

По умолчанию примеры слушают loopback 127.0.0.1, а урок [«07. IPv6-клиент и сервер»](07-ipv6/README.md) — IPv6 ::1.
Loopback не открывает сервер другим компьютерам.
В уроке [«14. Обнаружение устройств через UDP»](14-udp-discovery/README.md) broadcast/multicast включаются отдельными аргументами;
эти режимы могут использовать локальную сеть и слушать 0.0.0.0.
Для HTTP-клиентов можно явно передать URL, для HTTPS по умолчанию используется
https://example.com/; остальные стандартные запуски не требуют Интернета.

## Windows

Используются MSYS2 MinGW64, g++ и GDB, как в основном проекте.
WinSock инициализируется через `WSAStartup()`, сокет имеет тип `SOCKET`,
закрывается через `closesocket()`. Сборка добавляет -lws2_32.

HTTP/HTTPS-клиенты требуют libcurl от того же окружения MinGW64.
Если она ещё не установлена, в терминале MSYS2 выполните:

~~~bash
pacman -S --needed mingw-w64-x86_64-curl
~~~

C:/msys64/mingw64/bin должен быть в `PATH` для загрузки DLL.
При стандартной установке проекта дополнительных путей заголовков не требуется.
Не смешивайте библиотеки MinGW64 и UCRT64.
[Пакет libcurl в MSYS2](https://packages.msys2.org/packages/mingw-w64-x86_64-curl).

Уроки [«Асинхронный TCP-сервер»](22-asio/README.md),
[«WebSocket»](23-websocket/README.md), [«WSS»](24-wss/README.md),
[«Asio и strand»](25-asio-strand/README.md) и [«Итоговый чат»](31-chat/README.md)
дополнительно требуют заголовки Boost (`Boost.Asio`, а для WebSocket — `Boost.Beast`):

~~~bash
pacman -S --needed mingw-w64-x86_64-boost
~~~

[Пакет Boost в MSYS2](https://packages.msys2.org/packages/mingw-w64-x86_64-boost).
Отдельная standalone Asio не нужна: эти уроки используют `Boost.Asio`.

[WSS](24-wss/README.md) дополнительно использует OpenSSL напрямую:

~~~bash
pacman -S --needed mingw-w64-x86_64-openssl
~~~

[HTTP/2–3](20-http-versions/README.md) требует `libcurl >= 7.88`;
программа с `--features` показывает доступные протоколы загруженной библиотеки.

## Linux

Используются POSIX-сокеты: файловый дескриптор `int`, `close()`, `fcntl()`.
На Debian/Ubuntu зависимости можно установить так:

~~~bash
sudo apt-get install g++ gdb libcurl4-openssl-dev python3 openssl
~~~

libcurl требуется для HTTP/HTTPS-клиентов. Python и OpenSSL нужны
для локальных интеграционных проверок, но не для обычного запуска TCP/UDP.
Для [асинхронного сервера](22-asio/README.md),
[WebSocket](23-websocket/README.md), [WSS](24-wss/README.md),
[пула Asio](25-asio-strand/README.md) и [чата](31-chat/README.md)
установите также `libboost-dev`:

~~~bash
sudo apt-get install libboost-dev
~~~

Для [WSS](24-wss/README.md) нужен также пакет `libssl-dev`.
[HTTP/2–3](20-http-versions/README.md) требует `libcurl >= 7.88` с
соответствующими транспортами; обычная системная сборка может не иметь HTTP/3.
[Отдельная установка curl с HTTP/2 и HTTP/3](linux-curl.md) описывает сборку
в `/home`, размещение выпусков в `/opt/curl`, переключение ссылок и `CURL_PREFIX`.
Полные проверки новых протоколов требуют дополнительного
[Python-окружения](tests/README.md#зависимости-python) на обеих системах.

## Сборка и запуск

Команды выполняются из корня cpp-simplecode-lessons.
Каждый .cpp — отдельная программа; `server.cpp` и `client.cpp` не связываются вместе.
Пример на Linux:

~~~bash
bash scripts/build-linux.sh additions/networking/03-tcp-echo/server.cpp
bash scripts/build-linux.sh additions/networking/03-tcp-echo/client.cpp
~~~

В первом терминале:

~~~bash
./build/additions/networking/03-tcp-echo/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/additions/networking/03-tcp-echo/client
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/03-tcp-echo/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/03-tcp-echo/client.cpp
~~~

В первом терминале:

~~~powershell
& .\build\additions\networking\03-tcp-echo\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\additions\networking\03-tcp-echo\client.exe
~~~

В README каждого урока приведены его команды.
Серверы уроков от [TCP echo](03-tcp-echo/README.md) до
[WebSocket](23-websocket/README.md) конечны: обычно один клиент/запрос; у API пять запросов,
у многопользовательского примера и Asio три клиента. Ожидание подключения
ограничено 15 секундами: при таймауте перезапустите сервер.
Урок [«10. Переподключение, backoff и отмена»](10-reconnect/README.md) дополнительно показывает запуск клиента раньше готовности сервера.
[Итоговый чат](31-chat/README.md) работает до `/quit` или EOF консоли;
его клиенты восстанавливают соединение после перезапуска сервера.
[WSS](24-wss/README.md) принимает одного клиента и требует сертификат
и ключ в аргументах; [пул Asio](25-asio-strand/README.md) — три клиента.
[MQTT](28-mqtt/README.md) требует заранее запущенный локальный брокер,
а [HTTP/2–3](20-http-versions/README.md) — совместимую службу для выбранного режима.

Для TCP/UDP можно передать порт первым аргументом обеим программам.
Порт 0 у сервера выбирает свободный порт автоматически и печатает его.
HTTP-клиентам передаётся целый URL, API-клиенту — базовый URL без завершающего /.
В уроке [«07. IPv6-клиент и сервер»](07-ipv6/README.md) клиент принимает имя после порта, а discovery — режим и интерфейс.
В остальных нативных TCP-примерах адрес сервера остаётся loopback.

## VS Code

Откройте корень проекта или папку конкретного урока.
Обновите IntelliSense задачей C/C++: Update IntelliSense.
Активный .cpp можно собрать и запустить через F5/Ctrl+F5.
Сначала должен быть запущен сервер, затем клиент.

При открытии отдельного урока с парой программ доступны задачи:

- Networking: Run server — соберёт `server.cpp` и запустит в своём терминале.
- Networking: Run client — соберёт `client.cpp` и запустит в другом терминале.

Запустите первую задачу, дождитесь Listening, затем вторую.
Не задавайте зависимость «дождаться завершения сервера перед клиентом»:
сервер сам ждёт клиента. Автоматического одновременного старта здесь нет.
Для F5/Ctrl+F5 удобно оставить сервер работающим в терминале, а отлаживать `client.cpp`.
Сами папки additions/ и networking/ не являются отдельными рабочими областями VS Code.

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
- [common/boost_net.hpp](common/boost_net.hpp) — заголовки и настройка `Boost.Asio` для Windows/Linux.

Общий код вынесен, чтобы в уроках были видны действия клиента и сервера,
а не повторяющиеся платформенные ветки. Его функции — часть учебного материала:
открывайте реализацию по мере изучения соответствующего вызова.
JSON-парсер понимает только объект с одним целочисленным полем `value`.
Для произвольного JSON и полноценного HTTP-сервера нужны соответствующие библиотеки.

`link-libraries.txt` рядом с исходниками задаёт нужные библиотеки:
`ws2_32`/`mswsock` на Windows, `curl` для HTTP/HTTPS, `ssl`/`crypto` для WSS.
Общие скрипты читают этот файл.
Для компиляции без линковки IntelliSense эти -l-флаги не нужны.

## Локальная проверка

Сначала соберите все .cpp. На Linux из корня:

~~~bash
for source in additions/networking/[0-9][0-9]-*/*.cpp; do bash scripts/build-linux.sh "$source" || break; done
python3 additions/networking/tests/smoke.py
~~~

На Windows из PowerShell:

~~~powershell
Get-ChildItem additions\networking\[0-9][0-9]-*\*.cpp | ForEach-Object {
    & C:\msys64\usr\bin\bash.exe scripts/build-windows.sh $_.FullName
    if ($LASTEXITCODE -ne 0) { throw "Build failed" }
}
python additions/networking/tests/smoke.py
~~~

Проверка обращается только к loopback. Она проверяет echo, кадры с нулевым байтом,
таймаут, недоступный порт, HTTP-ошибки, API, параллельных клиентов и фоновую отправку.
Для HTTPS создаётся временный самоподписанный сертификат: проверяются доверенный CA,
отсутствие доверия и несовпадение имени. Нужен openssl в `PATH`.
Явный параметр --skip-tls пропускает только эти проверки.

После сборки уроков от [IPv6](07-ipv6/README.md) до
[итогового чата](31-chat/README.md) выполните расширенную проверку:

~~~bash
build/networking-checks-venv/bin/python -B additions/networking/tests/smoke_extended.py
~~~

Сначала подготовьте [окружение проверок](tests/README.md#зависимости-python).
На Windows используйте `build\networking-checks-venv\Scripts\python.exe`.
Она проверяет IPv6 loopback,
переподключение и отмену, heartbeat, потерю ACK, файлы, discovery, Asio, WebSocket,
WSS, многопоточный Asio, MQTT, HTTP/2–3 и итоговый чат.
Для чата проверяются также рассылка, перезапуск сервера,
восстановление после отсутствующего `PONG` и управляемый выход.
Данные передачи файлов создаются во временном каталоге внутри build/.
Файловые проверки включают пустой файл, известную CRC32, ошибочную сумму,
недопустимое имя и предел размера.

Только итоговый чат можно проверить отдельно после сборки его двух программ:

~~~bash
python3 additions/networking/tests/smoke_chat.py
~~~

На Windows используйте `python` вместо `python3`. Проверка сама подаёт консольный
ввод и останавливает процессы; открывать дополнительные терминалы не требуется.

Дополнительно можно проверить multicast именно через loopback:

~~~bash
build/networking-checks-venv/bin/python -B additions/networking/tests/smoke_extended.py --multicast
~~~

LAN broadcast эти тесты не отправляют. Он проверяется вручную
только при явном выборе соответствующего режима в уроке [«14. Обнаружение устройств через UDP»](14-udp-discovery/README.md).

## Справочные материалы

- [WinSock: инициализация](https://learn.microsoft.com/en-us/windows/win32/winsock/initializing-winsock).
- [WinSock: неблокирующий ввод-вывод](https://learn.microsoft.com/en-us/windows/win32/winsock/nonblocking-i-o-2).
- [TCP — RFC 9293](https://www.rfc-editor.org/rfc/rfc9293.html).
- [HTTP semantics — RFC 9110](https://www.rfc-editor.org/rfc/rfc9110.html).
- [HTTP/1.1 — RFC 9112](https://www.rfc-editor.org/rfc/rfc9112.html).
- [libcurl](https://curl.se/libcurl/c/).
- [REST: описание автора](https://ics.uci.edu/~fielding/pubs/dissertation/rest_arch_style.htm).

[Дополнительные направления](../README.md). [Все уроки](../../LESSONS.md).
