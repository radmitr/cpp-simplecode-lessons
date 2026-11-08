# 09. Ограничения и SQLSTATE

## Версия C++

`auto`, лямбды — **C++11**.
`std::runtime_error` — **C++98**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.
libpq/PostgreSQL — внешняя зависимость со своей версией; версия C++ относится к клиентскому исходнику.

## Что изучаем

База проверяет корректность данных независимо от того, какая программа их пишет.

## Примеры

- [main.cpp](main.cpp).

Выбирайте один исходник с `main()`; варианты запускаются отдельно.

## Как это работает

- `PRIMARY` KEY — уникальный непустой идентификатор.
- `UNIQUE` — запрет повторов email.
- `NOT NULL` — обязательное значение.
- `CHECK(age >= 0)` — допустимый диапазон возраста.
  Сам `CHECK` не запрещает `NULL`, поэтому рядом нужен `NOT NULL`.

После одной корректной записи три `INSERT` намеренно нарушают ограничения:

~~~text
Rejected: 23505
Rejected: 23514
Rejected: 23502
Valid rows: 1
~~~

Это SQLSTATE: стабильный пятисимвольный код ошибки. Соответственно —
unique_violation, check_violation, not_null_violation.
`PQresultErrorField(result, PG_DIAG_SQLSTATE)` получает код.
Текст сообщения полезен человеку, а логику обработки лучше связывать с кодом.

Запросы выполняются вне явного `BEGIN`: каждый — отдельная транзакция autocommit.
Поэтому ошибочный `INSERT` не отменяет предыдущую успешную строку.
Внутри явной транзакции после SQL-ошибки требуется откат — урок [«13. Точки сохранения»](../13-savepoints/README.md).

[Ограничения](https://www.postgresql.org/docs/current/ddl-constraints.html) ·
[SQLSTATE](https://www.postgresql.org/docs/current/errcodes-appendix.html).

## Сборка и запуск

[Запуск в VS Code](../../../../README.md#сборка-и-запуск-в-vs-code).

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают `main.cpp` и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash additions/databases/postgresql/scripts/run.sh 09
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe additions/databases/postgresql/scripts/run.sh 09
~~~

В VS Code откройте `main.cpp` и нажмите F5/Ctrl+F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).

## Связанные темы и источники

[Версии C++](../../../../docs/cpp-versions.md) · [Как читать справочники](../../../../docs/references.md).
