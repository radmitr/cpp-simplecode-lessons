# 01. Подключение и первый SELECT

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

Программа подключается к учебной базе cpp_lessons, выводит её имя, версию
сервера и результат SELECT 2 + 3.

- PostgreSQL — отдельный сервер. Программа C++ обращается к нему через libpq.
- PQconnectdbParams получает массивы имён параметров и их значений.
  В common/db.hpp заданы адрес, порт, база, роль и путь к файлу пароля.
- CONNECTION_OK означает успешное подключение. При ошибке читается PQerrorMessage.
- PQexec выполняет SQL синхронно: вызывающий поток ждёт результат.
- У SELECT проверяется PGRES_TUPLES_OK. PQntuples — число строк,
  PQnfields — число столбцов; индексы PQgetvalue начинаются с нуля.
- PGconn и PGresult — разные объекты. Их освобождают PQfinish и PQclear;
  наши unique_ptr вызывают эти функции автоматически.

~~~text
Connected: cpp_lessons
Server version: 180006
Answer: 5
~~~

Число версии зависит от установленного сервера: 180006 означает 18.6.
Если сервер выключен, программа завершится с кодом 1 и сообщением об ошибке,
а не будет работать бесконечно. connect_timeout ограничивает подключение.

[libpq: подключение](https://www.postgresql.org/docs/current/libpq-connect.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 01
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 01
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
