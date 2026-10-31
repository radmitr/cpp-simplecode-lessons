# 03. INSERT и RETURNING

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

INSERT добавляет строки. Список столбцов показывает, каким полям соответствуют
значения; id не указан, поэтому его генерирует IDENTITY.

~~~sql
INSERT INTO notes(title) VALUES ('Learn SQL') RETURNING id, title;
~~~

RETURNING возвращает значения именно вставленных строк. Не нужно отдельным
SELECT искать max(id): другой клиент мог уже вставить свою строку.

Первый запрос добавляет одну запись, второй — две одним INSERT:

~~~text
1 | Learn SQL
2 | Learn C++
3 | Practice
~~~

У INSERT без RETURNING обычный успешный статус — PGRES_COMMAND_OK,
с RETURNING — PGRES_TUPLES_OK. db::checked принимает оба.
Последовательность id может иметь пропуски: откат транзакции не обязан
возвращать уже выданный номер. Не используйте id как непрерывный счётчик строк.

В этом вводном примере значения постоянные; ввод пользователя передаётся
параметрами, как в уроке 06.

[INSERT](https://www.postgresql.org/docs/current/sql-insert.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 03
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 03
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
