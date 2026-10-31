# 20. Резервная копия и проверка восстановления

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

main.cpp создаёт постоянную учебную схему backup_demo с двумя заметками.
Это исключение из большинства уроков с временными таблицами:
данные должны существовать после закрытия программы для pg_dump.

После запуска main.cpp выполните из корня репозитория:

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/backup-restore.sh
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/backup-restore.sh
~~~

Скрипт выполняет полную последовательность:

1. pg_dump --format=custom --schema=backup_demo сохраняет структуру и данные
   выбранной схемы в .local/postgresql/backups/notes.dump.
2. createdb создаёт новую базу `cpp_restore_<время>_<pid>`.
3. pg_restore --exit-on-error --single-transaction восстанавливает архив туда.
4. Два SELECT сравнивают упорядоченные строки исходной и восстановленной таблиц.

Ожидаются Backup verified и строки:

~~~text
1:Learn PostgreSQL
2:Verify restore
~~~

Существующие базы не удаляются. Восстановленная база остаётся для осмотра;
её имя напечатано в Restored database. Повтор создаёт ещё одну базу,
архив notes.dump при этом обновляется. Для осмотра:

~~~bash
bash bonus/databases/postgresql/scripts/lab.sh psql -d ИМЯ_ИЗ_ВЫВОДА
~~~

В psql: `SELECT * FROM backup_demo.notes;` затем `\q`.

Это логическая копия одной схемы, не всего кластера. Роли и глобальные объекты
она не сохраняет; зависимости от объектов вне схемы требуют отдельного учёта.
Для копии всей базы убирают --schema, глобальные объекты сохраняют pg_dumpall
--globals-only; физические копии и PITR — отдельная тема.
pg_dump не должен быть старше major-версии сервера. Архив custom восстанавливают
через pg_restore, обычный SQL-дамп — через psql.

Факт создания файла ещё не подтверждает пригодность копии:
нужны восстановление и проверка данных.
[pg_dump](https://www.postgresql.org/docs/current/app-pgdump.html) ·
[pg_restore](https://www.postgresql.org/docs/current/app-pgrestore.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 20
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 20
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
