# 01. Адреса, DNS и порядок байтов

## Версия C++

`std::unique_ptr`, `std::to_string`, `nullptr`, `decltype`, лямбды — **C++11**.
`std::exception`, `std::runtime_error` — **C++98**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.
WinSock/POSIX-сокеты — платформенные API, не часть стандарта C++.

## Что изучаем

`main.cpp` вызывает `getaddrinfo()` для localhost и службы 80.
`AF_UNSPEC` разрешает IPv4 и IPv6; в отличие от `inet_pton()`, `getaddrinfo()`
может разрешать имя, а не только разбирать готовую строку IP.

Windows: MinGW64; Linux: POSIX.

## Примеры

- [main.cpp](main.cpp).

Выбирайте один исходник с `main()`; варианты запускаются отдельно.

## Как это работает

Результат — список `addrinfo`. Он освобождается через `freeaddrinfo()`
при уничтожении `unique_ptr`. Для каждого адреса `inet_ntop()` получает
читаемую строку. Количество и порядок адресов зависят от ОС и её настроек.

Обычно можно увидеть 127.0.0.1 и ::1. localhost может браться из локального
файла hosts: обращение к DNS-серверу для него не обязательно.
Можно передать другое имя первым аргументом, например `example.com`;
это уже может потребовать сети.

`htons()`/`ntohs()` преобразуют 16-битный порт между порядком байтов машины
и сети. `htonl()`/`ntohl()` выполняют аналогичное преобразование для 32 бит.
Это не шифрование и не перевод числа в текст.

`net::Runtime` инициализирует WinSock на Windows. На Linux отдельная
инициализация сокетной подсистемы не требуется. Runtime создаётся раньше
сетевых объектов и уничтожается после них.

## Сборка и запуск

[Запуск в VS Code](../../../README.md#сборка-и-запуск-в-vs-code).

Из корня репозитория на Linux:

~~~bash
bash scripts/build-linux.sh additions/networking/01-addresses/main.cpp
./build/additions/networking/01-addresses/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/01-addresses/main.cpp
& .\build\additions\networking\01-addresses\main.exe
~~~

Откройте `main.cpp` для запуска через F5/Ctrl+F5.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).

## Связанные темы и источники

### Дополнительные API в коде

- [Исключительное владение unique_ptr](../../../basics/additions/12-unique-ptr/README.md): [полный пример](../../../basics/additions/12-unique-ptr/main.cpp).

[Версии C++](../../../docs/cpp-versions.md) · [Как читать справочники](../../../docs/references.md).
