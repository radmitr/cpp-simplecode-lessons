# 09. Параллельная обработка нескольких клиентов

C++17. Windows: MinGW64; Linux: POSIX.

Один слушающий сокет принимает три независимых TCP-соединения.
Для каждого принятого сокета std::async(std::launch::async, ...) запускает
обработчик. Сокет перемещается в лямбду и принадлежит только этому обработчику.

Общий listener не передаётся работникам. Каждый получает строку и отправляет echo
через свой клиентский сокет. Отдельный mutex защищает только печать целых строк,
а не весь сетевой обмен.

Клиентская программа тоже запускает три задачи, поэтому подключения могут
обслуживаться параллельно. Порядок строк не определён:

~~~text
Verified: client 1
Verified: client 2
Verified: client 3
~~~

Сервер в конце сообщает Handled clients: 3.
Каждый future.get() ждёт задачу и передаёт её исключение вызывающему коду.
Сохранённые futures от launch::async также обеспечивают ожидание при выходе
из области видимости, если ошибка случилась во время приёма других клиентов.

Один общий сокет, в который одновременно пишут несколько потоков, потребовал бы
отдельной политики сериализации сообщений. Здесь сокеты разные.
Создание задачи на каждого клиента подходит для этого ограниченного примера.
Для большого числа подключений нужны лимиты, пул или событийный ввод-вывод.
[Пул потоков](../../../multithreading/bonus/11-thread-pool/) можно изучить отдельно.

## Сборка и запуск

Порт по умолчанию: 42009. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-09-multi-client/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-09-multi-client/client.cpp
~~~

Первый терминал:

~~~bash
./build/bonus/networking/lesson-09-multi-client/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-09-multi-client/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-09-multi-client/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-09-multi-client/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\bonus\networking\lesson-09-multi-client\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-09-multi-client\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на client.cpp.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
