# 04. UDP echo и датаграммы

C++17. Windows: MinGW64; Linux: POSIX.

SOCK_DGRAM создаёт UDP-сокет. Сервер привязывает его к loopback-порту,
recvfrom() получает датаграмму и адрес отправителя, sendto() отправляет ответ.
У UDP в этом примере нет listen(), accept() и предварительного TCP-подключения.

Клиент отправляет Hello over UDP и ждёт ответ с тем же содержимым.
Он также проверяет адрес и порт отправителя. Ожидаемый вывод:

~~~text
Datagram echo: Hello over UDP
~~~

У UDP сохраняются границы датаграмм, но нет гарантий доставки, порядка
или отсутствия дубликатов. Успешный sendto() означает принятие данных локальной
системой, а не подтверждение доставки серверу. В этом примере подтверждением
на уровне приложения является echo. Автоматических повторов здесь нет.

Нулевая длина UDP-датаграммы допустима; recvfrom() == 0 не означает закрытие
UDP-соединения. В отличие от TCP, такого потока-соединения здесь вообще нет.

Учебный буфер равен 1024 байтам, отправляемое сообщение намного меньше.
Для слишком большой датаграммы поведение включает обрезание или ошибку
в зависимости от API и ОС: нельзя считать этот пример передачей любого файла.

## Сборка и запуск

Порт по умолчанию: 42004. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-04-udp-echo/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-04-udp-echo/client.cpp
~~~

Первый терминал:

~~~bash
./build/bonus/networking/lesson-04-udp-echo/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-04-udp-echo/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-04-udp-echo/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-04-udp-echo/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\bonus\networking\lesson-04-udp-echo\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-04-udp-echo\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на client.cpp.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
