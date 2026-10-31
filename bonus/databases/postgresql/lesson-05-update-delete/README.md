# 05. UPDATE и DELETE

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

UPDATE меняет существующие строки, DELETE удаляет их.
WHERE определяет, какие именно записи затронуть.

~~~sql
UPDATE tasks SET done = true WHERE id = 1 RETURNING id, done;
DELETE FROM tasks WHERE done = true RETURNING title;
~~~

Без WHERE обновление или удаление затронет все строки таблицы.
В примере удаляется только завершённая задача, а затем выполняется
DELETE с несуществующим id.

~~~text
1 | t
Deleted: 1
Missing id affected: 0
~~~

PQcmdTuples возвращает текстовое число затронутых строк. Ноль означает,
что подходящих записей не было; это нормальный результат.
RETURNING позволяет получить изменённые/удалённые данные без второго запроса.

Это изменения данных, а DROP TABLE удаляет саму таблицу вместе со структурой.
Если несколько изменений должны либо сохраниться вместе, либо полностью
отмениться, нужна транзакция — урок 12.

[UPDATE](https://www.postgresql.org/docs/current/sql-update.html) ·
[DELETE](https://www.postgresql.org/docs/current/sql-delete.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 05
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 05
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
