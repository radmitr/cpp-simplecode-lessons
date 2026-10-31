# 09. Ограничения и SQLSTATE

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

База проверяет корректность данных независимо от того, какая программа их пишет.

- PRIMARY KEY — уникальный непустой идентификатор.
- UNIQUE — запрет повторов email.
- NOT NULL — обязательное значение.
- CHECK(age >= 0) — допустимый диапазон возраста.
  Сам CHECK не запрещает NULL, поэтому рядом нужен NOT NULL.

После одной корректной записи три INSERT намеренно нарушают ограничения:

~~~text
Rejected: 23505
Rejected: 23514
Rejected: 23502
Valid rows: 1
~~~

Это SQLSTATE: стабильный пятисимвольный код ошибки. Соответственно —
unique_violation, check_violation, not_null_violation.
PQresultErrorField(result, PG_DIAG_SQLSTATE) получает код.
Текст сообщения полезен человеку, а логику обработки лучше связывать с кодом.

Запросы выполняются вне явного BEGIN: каждый — отдельная транзакция autocommit.
Поэтому ошибочный INSERT не отменяет предыдущую успешную строку.
Внутри явной транзакции после SQL-ошибки требуется откат — урок 13.

[Ограничения](https://www.postgresql.org/docs/current/ddl-constraints.html) ·
[SQLSTATE](https://www.postgresql.org/docs/current/errcodes-appendix.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 09
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 09
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
