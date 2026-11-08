# 24. WSS: WebSocket поверх TLS

## Версия C++

`std::shared_ptr`, `std::chrono` и лямбды — **C++11**, захват с инициализацией —
**C++14**. Сборка — **C++17**, как у сетевого раздела. `Boost.Beast`, `Boost.Asio`
и OpenSSL — внешние библиотеки; WSS не является возможностью стандарта C++.

## Что изучаем

Соединяем [HTTPS и проверку сертификата](../18-https/README.md) с
[WebSocket](../23-websocket/README.md): сначала защищённое соединение,
затем HTTP Upgrade, затем двусторонние сообщения. Нужны знания
[асинхронного Asio](../22-asio/README.md) и времени жизни буферов.

## Примеры

- [server.cpp](server.cpp) принимает одного клиента, посылает `tick 1`, `tick 2`,
  `tick 3`, получает `ACK 3` и закрывает соединение.
- [client.cpp](client.cpp) проверяет сертификат, читает три события и подтверждает их.
- [Проверки WSS](../tests/smoke_advanced.py) проверяют успешный обмен, недоверенный CA,
  несовпадение имени и клиента, не начавшего TLS handshake.

## Как это работает

Сервер загружает `cert.pem` и `key.pem` в `ssl::context`. Контекст хранит настройки
TLS и живёт до завершения `io.run()`; сессия использует его для TLS-обмена.
После TCP-подключения клиент запускает `async_handshake()` у **SSL-слоя**.
Сервер выполняет соответствующий handshake в роли сервера. OpenSSL согласует
параметры шифрования, а клиент проверяет сертификат. Минимум настроен на TLS 1.2.

Клиент включает `verify_peer` и доверяет переданному `ca.pem`. Отдельно
`ssl::host_name_verification(host)` проверяет, что сертификат выдан нужному имени.
Доверие к CA само по себе не проверяет имя. `SSL_set_tlsext_host_name()` задаёт
SNI — имя сервера в TLS-запросе, по которому сервер может выбрать сертификат.
SNI тоже не заменяет проверку имени. Аргумент `-` вместо CA включает системные
пути доверия OpenSSL: это не отключение проверки. В Windows они могут отличаться
от хранилища сертификатов операционной системы.

Только после успешного TLS клиент вызывает `async_handshake()` у **WebSocket-слоя**
с путём `/events`. Это другой handshake: HTTP-запрос Upgrade внутри уже защищённого
канала. Если перепутать порядок и послать HTTP на ожидающий TLS порт, соединение
не станет WSS. Стек `websocket::stream<beast::ssl_stream<Tcp::socket>>` отражает
порядок вложения: WebSocket → TLS → TCP. Вызов `next_layer()` опускается на слой,
а `beast::get_lowest_layer()` даёт TCP-сокет для подключения и окончательного закрытия.

Затем выполняется тот же обмен `tick`/`ACK`, что и в обычном WebSocket-примере.
`message_` и `ack_` — поля объекта: память не исчезает, пока `async_write()` ещё
использует её. Захват `shared_from_this()` удерживает сессию до обработчика.
Работает один поток `io.run()`, обработчики одной программы не исполняются параллельно.

Завершение тоже послойное: WebSocket Close, затем TLS-уведомление `close_notify`,
затем закрытие TCP. Beast выполняет TLS teardown автоматически благодаря
подключённому `<boost/beast/ssl.hpp>`; повторный ручной shutdown не нужен.
Клиент после отправки `ACK 3`
читает до WebSocket Close; это позволяет обработать служебный кадр закрытия.
Простой обрыв TCP пропустил бы корректное закрытие верхних слоёв.
Ошибки TLS teardown не маскируются как успешный обмен.

Сервер ждёт подключения 15 секунд. Общий таймер сессии ограничивает handshake,
обмен и закрытие пятью секундами; на клиенте действует такой же общий предел.
При ошибке сокет закрывается, таймеры отменяются, обработчики отмены завершаются,
`io.run()` возвращает управление. Сообщения ограничены 4096 байтами.

## Сборка и запуск

[Общие зависимости Windows](../README.md#windows), [Linux](../README.md#linux),
[F5/Ctrl+F5](../../../README.md#сборка-и-запуск-в-vs-code).
Дополнительно нужны заголовки и библиотеки OpenSSL:
`mingw-w64-x86_64-openssl` в MSYS2 MinGW64 или `libssl-dev` на Debian/Ubuntu.
Файл `link-libraries.txt` добавляет `ssl`, `crypto` и библиотеки WinSock на Windows.

Из корня проекта создайте [учебный сертификат](../tests/README.md#сертификат-для-ручных-примеров).
Linux, сборка двух отдельных программ:

```bash
bash scripts/build-linux.sh additions/networking/24-wss/server.cpp
bash scripts/build-linux.sh additions/networking/24-wss/client.cpp
```

Windows, PowerShell:

```powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/24-wss/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/24-wss/client.cpp
```

В двух терминалах из корня проекта, Linux:

```bash
./build/additions/networking/24-wss/server 42020 build/networking-tls/cert.pem build/networking-tls/key.pem
./build/additions/networking/24-wss/client 42020 build/networking-tls/cert.pem
```

Windows:

```powershell
& .\build\additions\networking\24-wss\server.exe 42020 build/networking-tls/cert.pem build/networking-tls/key.pem
& .\build\additions\networking\24-wss\client.exe 42020 build/networking-tls/cert.pem
```

Дождитесь `Listening` перед запуском клиента. Ввода с клавиатуры нет.
Аргументы: `server port certificate.pem key.pem`; `client port ca.pem|- [hostname]`.
Сервер разрешает порт `0`; клиенту нужен напечатанный фактический порт.
Адрес TCP всегда `127.0.0.1`; необязательное имя (по умолчанию `localhost`)
используется для SNI, проверки сертификата и заголовка Host, а не для DNS-поиска.

Клиент выводит `Event: tick 1` … `Event: tick 3` и `WSS complete: 3 events`;
сервер — `WSS completed: ACK 3`. Успех — код `0`, ошибка — `1`.
Если передать клиенту четвёртый аргумент `127.0.0.1`, учебный сертификат для
`localhost` будет отвергнут: это ожидаемая ошибка имени, а не ошибка TCP.
Сертификат с истёкшим сроком также не принимается.

В папке урока задачи `Networking: Run server/client` и конфигурации
`WSS: server/client` используют сертификат из `build/networking-tls/`.
В корневом VS Code задайте аргументы из команд выше вручную; обычный запуск
без аргументов здесь закономерно сообщает об ошибке.
Автоматический запуск: [установка окружения и `smoke_advanced.py`](../tests/README.md#зависимости-python).

## Типичные ошибки

- Считать `wss://` простой заменой текста URL без добавления TLS-слоя.
- Проверять цепочку сертификата, но забывать имя сервера, или отключать проверку.
- Уничтожать `ssl::context` до завершения сессий либо буфер до завершения записи.
- Ожидать поддержку WSS от обычного WebSocket-порта: последовательность handshake различается.

## Связанные темы и источники

- [WebSocket без TLS](../23-websocket/README.md).
- [HTTPS и доверенный CA](../18-https/README.md).
- [Boost.Asio: проверка имени](https://www.boost.org/doc/libs/latest/doc/html/boost_asio/reference/ssl__host_name_verification.html).
- [Boost.Beast: SSL streams](https://www.boost.org/doc/libs/latest/doc/html/boost_beast/ref/boost__beast__ssl_stream.html).
