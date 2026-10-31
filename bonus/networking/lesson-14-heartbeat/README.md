# 14. Heartbeat: PING/PONG

C++17. Windows: MinGW64; Linux: POSIX.

Одно TCP-соединение используется для трёх проверок приложения.
Клиент посылает PING с номером, сервер отвечает соответствующим PONG.

Первые два ответа приходят, а третий сервер намеренно пропускает,
не закрывая TCP-соединение. Клиент ждёт его 250 мс:

~~~text
PONG 1
PONG 2
Heartbeat timeout: peer application is not responding
~~~

Код возврата 0 здесь означает, что ожидаемый сценарий обнаружен.
Неверный номер PONG или преждевременная ошибка завершают пример с кодом 1.

Отсутствие ответа не позволяет точно отличить перегрузку приложения,
проблему сети и отказ устройства. Оно сообщает, что требуемый ответ
не получен в заданное время. Решение о переподключении принимает приложение.

Открытый TCP-сокет не доказывает, что удалённый обработчик продолжает работать.
Системный TCP keepalive проверяет соединение на другом уровне и не заменяет
такую прикладную проверку. В уроке keepalive ОС не настраивается.

Номера сообщений помогают не принять старый или чужой PONG за текущий.
Вместо произвольного sleep() для получения ответа используется чтение
с дедлайном. Пауза между успешными проверками изображает период мониторинга.
В реальной системе интервалы выбирают под ожидаемые задержки и нагрузку.

## Сборка и запуск

Команды выполняются из корня проекта. Порт по умолчанию — 42014.
Сначала соберите обе программы.

Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-14-heartbeat/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-14-heartbeat/client.cpp
~~~

В первом терминале:

~~~bash
./build/bonus/networking/lesson-14-heartbeat/server
~~~

Во втором терминале после Listening:

~~~bash
./build/bonus/networking/lesson-14-heartbeat/client
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-14-heartbeat/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-14-heartbeat/client.cpp
~~~

В первом терминале:

~~~powershell
& .\build\bonus\networking\lesson-14-heartbeat\server.exe
~~~

Во втором терминале после Listening:

~~~powershell
& .\build\bonus\networking\lesson-14-heartbeat\client.exe
~~~

При открытии папки урока в VS Code используйте Networking: Run server,
затем Networking: Run client. Задачи соберут нужные исходники и запустят их
в разных терминалах. Для отладки клиента оставьте сервер в терминале
и нажмите F5 на client.cpp. Дополнительные аргументы можно передавать из терминала.
После добавления исходников обновите C/C++: Update IntelliSense.

[Зависимости, общий код и все сетевые уроки](../README.md).
