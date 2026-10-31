# 01. Адреса, DNS и порядок байтов

C++17. Windows: MinGW64; Linux: POSIX.

main.cpp вызывает getaddrinfo() для localhost и службы 80.
AF_UNSPEC разрешает IPv4 и IPv6; в отличие от inet_pton(), getaddrinfo()
может разрешать имя, а не только разбирать готовую строку IP.

Результат — список addrinfo. Он освобождается через freeaddrinfo()
при уничтожении unique_ptr. Для каждого адреса inet_ntop() получает
читаемую строку. Количество и порядок адресов зависят от ОС и её настроек.

Обычно можно увидеть 127.0.0.1 и ::1. localhost может браться из локального
файла hosts: обращение к DNS-серверу для него не обязательно.
Можно передать другое имя первым аргументом, например example.com;
это уже может потребовать сети.

htons()/ntohs() преобразуют 16-битный порт между порядком байтов машины
и сети. htonl()/ntohl() выполняют аналогичное преобразование для 32 бит.
Это не шифрование и не перевод числа в текст.

net::Runtime инициализирует WinSock на Windows. На Linux отдельная
инициализация сокетной подсистемы не требуется. Runtime создаётся раньше
сетевых объектов и уничтожается после них.

## Сборка и запуск

Из корня репозитория на Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-01-addresses/main.cpp
./build/bonus/networking/lesson-01-addresses/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-01-addresses/main.cpp
& .\build\bonus\networking\lesson-01-addresses\main.exe
~~~

Откройте main.cpp для запуска через F5/Ctrl+F5.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
