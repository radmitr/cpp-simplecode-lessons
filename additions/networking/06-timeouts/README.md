# 06. Неблокирующие сокеты, таймауты и ошибки

## Версия C++

`std::chrono`, `auto` — **C++11**.
`std::exception`, `std::runtime_error` — **C++98**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.
WinSock/POSIX-сокеты — платформенные API, не часть стандарта C++.

## Что изучаем

Сервер принимает строку Please reply, но намеренно не отвечает.
Клиент ждёт до своего deadline около 200 мс и обрабатывает `net::Timeout`:

Windows: MinGW64; Linux: POSIX.

## Примеры

- [client.cpp](client.cpp).
- [server.cpp](server.cpp).

Сервер и клиент — две отдельные программы. Нужны обе: сначала сервер
в одном терминале, затем клиент в другом. Каждый исходник собирается отдельно.

## Как это работает

~~~text
Expected timeout: no response within the deadline
~~~

После выхода из `main` клиент закрывает сокет через RAII.
Сервер узнаёт об этом по `recv() == 0` и завершает работу.
Таймаут и закрытие соединения — разные события.

В `common/net.hpp` сокеты неблокирующие:
`ioctlsocket(FIONBIO)` на Windows, `fcntl(O_NONBLOCK)` на Linux.
Когда операция пока невозможна, API сообщает `WSAEWOULDBLOCK` либо
EAGAIN/EWOULDBLOCK. `select()` ждёт готовности, затем операция пробуется снова.
Готовность не отменяет проверку результата `send()`/`recv()`.

Неблокирующий `connect()` может сообщить, что подключение ещё выполняется.
После готовности на запись нужно проверить `getsockopt(SO_ERROR)`:
готовность сама по себе не доказывает успешного подключения.

Дедлайн основан на steady_clock. Повтор после EINTR или частичного обмена
использует прежний момент, поэтому таймаут не начинается заново.
Точное время возврата зависит также от планировщика.

Если сервер не запущен, клиент может получить отказ подключения либо
истечение дедлайна — это зависит от ОС и сетевых настроек.
Не делайте бесконечные быстрые повторные `connect()`: повторной попытке
нужны ограничение количества/времени и пауза. Этот пример завершает работу
с ошибкой; политику повторов приложение выбирает отдельно.

## Сборка и запуск

[Запуск в VS Code](../../../README.md#сборка-и-запуск-в-vs-code).

Порт по умолчанию: 42005. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh additions/networking/06-timeouts/server.cpp
bash scripts/build-linux.sh additions/networking/06-timeouts/client.cpp
~~~

Первый терминал:

~~~bash
./build/additions/networking/06-timeouts/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/additions/networking/06-timeouts/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/06-timeouts/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/06-timeouts/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\additions\networking\06-timeouts\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\additions\networking\06-timeouts\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run `client`. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на `client.cpp`.
Для запуска без отладки используйте Ctrl+F5.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).

## Связанные темы и источники

[Версии C++](../../../docs/cpp-versions.md) · [Как читать справочники](../../../docs/references.md).
