# 19. Массовая загрузка и выгрузка COPY

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

COPY передаёт набор строк потоком вместо отдельного INSERT на каждую запись.
Пример загружает три CSV-строки через соединение и читает их обратно.

~~~text
Imported rows: 3
Exported CSV:
1,10
2,20
3,30
~~~

Для COPY FROM STDIN:

1. PQexec переводит соединение в PGRES_COPY_IN.
2. PQputCopyData отправляет байты; границы блоков не являются границами строк.
3. PQputCopyEnd завершает отправку.
4. PQgetResult получает итог команды; результат обязательно проверяется.

Для COPY TO STDOUT используются PGRES_COPY_OUT и PQgetCopyData.
Положительное значение — размер полученного блока; -1 — завершение,
-2 — ошибка. Память блока освобождается PQfreemem.
После передачи снова читаются итоговые результаты до nullptr.

В примере соединение блокирующее; вариант с nonblocking требует обработки
готовности сокета и неполной отправки. В CSV с текстом также нужны правила
кавычек, запятых и переводов строки; не склеивайте произвольный текст как CSV
без корректного кодировщика.

COPY ... STDIN/STDOUT работает через клиента.
COPY ... '/server/file' читает файл на стороне сервера и требует других прав.
COPY переносит данные, но не заменяет резервную копию структуры и объектов.

[libpq: COPY](https://www.postgresql.org/docs/current/libpq-copy.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 19
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 19
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
