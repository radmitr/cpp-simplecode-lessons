# 08. NULL и пустая строка

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

NULL означает отсутствие значения. Пустая строка — существующее значение
длиной ноль. В примере создаются оба случая.

- В массиве параметров nullptr обозначает SQL NULL.
- Указатель на строку "" передаёт пустой текст.
- PQgetisnull проверяет отсутствие значения.
- PQgetvalue для NULL тоже возвращает пустую строку: по нему одному
  отличить два случая нельзя.

~~~text
1: <NULL>
2: <empty string>
NULL count: 1
~~~

В SQL пишут IS NULL и IS NOT NULL. Выражение nickname = NULL не проверяет
отсутствие: обычное сравнение с NULL даёт неизвестный результат.
WHERE оставляет только строки с истинным условием.

COALESCE(nickname, 'guest') может подставить значение для отображения.
В модели C++ отсутствие часто представляют `std::optional<T>`.
Текстовый протокол libpq возвращает числа текстом: при преобразовании
нужно учитывать диапазон и ошибки, а не читать память как готовый int.

[NULL и сравнения](https://www.postgresql.org/docs/current/functions-comparison.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 08
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 08
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
