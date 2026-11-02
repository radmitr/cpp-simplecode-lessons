# 15. ACK, request_id и защита от повторного выполнения

## Версия C++

`std::chrono`, `auto`, лямбды, `std::to_string` — **C++11**.
`std::string`, `std::exception`, `std::runtime_error`, `std::map` — **C++98**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.
WinSock/POSIX-сокеты — платформенные API, не часть стандарта C++.

## Что изучаем

Клиент передаёт ADD req-1 5. Сервер прибавляет 5 к общему значению,
но намеренно закрывает первое соединение без ACK.
Клиент уже не может по одному факту закрытия понять, была ли команда выполнена.

Windows: MinGW64; Linux: POSIX.

## Примеры

- [client.cpp](client.cpp).
- [server.cpp](server.cpp).

Сервер и клиент — две отдельные программы. Нужны обе: сначала сервер
в одном терминале, затем клиент в другом. Каждый исходник собирается отдельно.

## Как это работает

Он повторяет тот же request_id и то же содержимое.
Сервер находит запись в `completed` и возвращает сохранённый результат,
не выполняя прибавление второй раз.

Третий запрос использует тот же id, но другое число — это конфликт:

~~~text
ACK was lost; retrying the same request_id and payload
ACK req-1 5
ERROR req-1 conflict
~~~

Сервер подтверждает:

~~~text
Applications: 1
Total: 5
~~~

Успешный `send()` подтверждает принятие данных локальным стеком.
Прикладной ACK показывает, что сервер обработал команду по своему протоколу.
Кэш результата связывает id с содержимым запроса и его результатом.

Этот пример хранит кэш только в памяти и принимает ровно три соединения.
После перезапуска история теряется. Это не универсальная гарантия exactly-once:
для устойчивости к сбою нужны сохранение результата и согласование его записи
с изменением состояния. У реального кэша также нужны ограничения размера и срока жизни.

В HTTP нельзя бездумно повторять операции, которые могут изменить состояние
повторно. Идентификатор операции — один из способов организовать безопасный повтор.
[Повторные HTTP-запросы](https://www.rfc-editor.org/rfc/rfc9110.html#name-retrying-requests).

## Сборка и запуск

[Запуск в VS Code](../../../README.md#сборка-и-запуск-в-vs-code).

Команды выполняются из корня проекта. Порт по умолчанию — 42015.
Сначала соберите обе программы.

Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-15-request-ack/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-15-request-ack/client.cpp
~~~

В первом терминале:

~~~bash
./build/bonus/networking/lesson-15-request-ack/server
~~~

Во втором терминале после Listening:

~~~bash
./build/bonus/networking/lesson-15-request-ack/client
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-15-request-ack/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-15-request-ack/client.cpp
~~~

В первом терминале:

~~~powershell
& .\build\bonus\networking\lesson-15-request-ack\server.exe
~~~

Во втором терминале после Listening:

~~~powershell
& .\build\bonus\networking\lesson-15-request-ack\client.exe
~~~

При открытии папки урока в VS Code используйте Networking: Run server,
затем Networking: Run `client`. Задачи соберут нужные исходники и запустят их
в разных терминалах. Для отладки клиента оставьте сервер в терминале
и нажмите F5 на `client.cpp`. Дополнительные аргументы можно передавать из терминала.
После добавления исходников обновите C/C++: Update IntelliSense.
Для запуска без отладки используйте Ctrl+F5.

[Зависимости, общий код и все сетевые уроки](../README.md).

## Связанные темы и источники

[Версии C++](../../../docs/cpp-versions.md) · [Как читать справочники](../../../docs/references.md).
