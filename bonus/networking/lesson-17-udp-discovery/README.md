# 17. Обнаружение устройств через UDP

C++17. Windows: MinGW64; Linux: POSIX.

Клиент посылает DISCOVER с новым nonce.
Сервер отвечает DEVICE demo-device с тем же nonce.
Клиент принимает ответы в трёх ограниченных окнах по 200 мс,
отбрасывает чужой nonce и выводит каждый найденный IP:порт один раз.

По умолчанию обе программы используют unicast через 127.0.0.1.
Ожидается:

~~~text
Found demo-device at 127.0.0.1:42017
Discovered devices: 1
~~~

Повторные ответы одного сервера не создают новые записи.
Nonce связывает ответ с текущим поиском; он не является аутентификацией.
UDP не гарантирует доставку. Потеря всех запросов или ответов даст пустой результат.

## Режимы

Обе программы принимают дополнительные аргументы:

~~~text
program [port] [unicast|broadcast|multicast] [interface-ip]
~~~

unicast адресует один известный узел. Этот режим используется в обычных
задачах VS Code и не требует доступа к локальной сети.

broadcast включает SO_BROADCAST и отправляет запрос на 255.255.255.255.
Сервер в этом режиме слушает 0.0.0.0. Режим выбирается явно:

~~~text
server 42017 broadcast
client 42017 broadcast
~~~

Эти команды обращаются к локальной сети; результат зависит от интерфейса,
брандмауэра, Wi-Fi isolation и сетевых настроек. При нескольких интерфейсах
можно явно передать IPv4 нужного интерфейса третьим аргументом.

multicast использует группу 239.255.42.99.
Сервер вступает в группу через IP_ADD_MEMBERSHIP, клиент задаёт интерфейс
через IP_MULTICAST_IF. TTL=1 ограничивает распространение, а multicast loop
позволяет принимать локальные отправки.

Для сравнения на одном компьютере явно выберите loopback в обоих терминалах:

~~~text
server 42017 multicast 127.0.0.1
client 42017 multicast 127.0.0.1
~~~

Поддержка такого multicast зависит от ОС и конфигурации сети.
В LAN укажите адрес её интерфейса, а не 127.0.0.1.
Пример не настраивает маршрутизаторы и не является реализацией mDNS/SSDP.
[Рекомендации по UDP](https://www.rfc-editor.org/rfc/rfc8085.html).

## Сборка и запуск

Команды выполняются из корня проекта. Порт по умолчанию — 42017.
Сначала соберите обе программы.

Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-17-udp-discovery/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-17-udp-discovery/client.cpp
~~~

В первом терминале:

~~~bash
./build/bonus/networking/lesson-17-udp-discovery/server
~~~

Во втором терминале после Listening:

~~~bash
./build/bonus/networking/lesson-17-udp-discovery/client
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-17-udp-discovery/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-17-udp-discovery/client.cpp
~~~

В первом терминале:

~~~powershell
& .\build\bonus\networking\lesson-17-udp-discovery\server.exe
~~~

Во втором терминале после Listening:

~~~powershell
& .\build\bonus\networking\lesson-17-udp-discovery\client.exe
~~~

При открытии папки урока в VS Code используйте Networking: Run server,
затем Networking: Run client. Задачи соберут нужные исходники и запустят их
в разных терминалах. Для отладки клиента оставьте сервер в терминале
и нажмите F5 на client.cpp. Дополнительные аргументы можно передавать из терминала.
После добавления исходников обновите C/C++: Update IntelliSense.

[Зависимости, общий код и все сетевые уроки](../README.md).
