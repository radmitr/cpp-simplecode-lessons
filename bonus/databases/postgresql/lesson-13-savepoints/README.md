# 13. Точки сохранения

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

SAVEPOINT отмечает место внутри транзакции. ROLLBACK TO SAVEPOINT отменяет
только изменения после этой точки и позволяет продолжить транзакцию.

В примере:

1. BEGIN и успешный INSERT id = 1.
2. SAVEPOINT optional_step.
3. Повторный id = 1 вызывает SQLSTATE 23505.
4. ROLLBACK TO SAVEPOINT восстанавливает работоспособное состояние.
5. RELEASE удаляет точку, затем добавляется id = 2 и выполняется COMMIT.

~~~text
Committed ids:
1
2
~~~

После SQL-ошибки внутри BEGIN одного catch в C++ недостаточно:
состояние серверной транзакции остаётся ошибочным.
Без отката обычные запросы получат 25P02 (in_failed_sql_transaction).

ROLLBACK TO сохраняет саму точку, RELEASE её удаляет.
RELEASE не равен COMMIT: окончательная фиксация всей транзакции ещё впереди.
Если выполнить полный ROLLBACK, отменятся и строки до точки сохранения.

[SAVEPOINT](https://www.postgresql.org/docs/current/sql-savepoint.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 13
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 13
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
