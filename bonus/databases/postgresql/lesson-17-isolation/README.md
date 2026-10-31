# 17. Изоляция и снимки данных

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

Пример использует два независимых соединения reader и writer.
C++ вызывает их последовательно, но транзакция reader остаётся открытой,
пока writer фиксирует изменение. Для наблюдения изоляции отдельный std::thread
не обязателен.

~~~text
READ COMMITTED: 10 -> 20
REPEATABLE READ: 10 -> 10
~~~

При READ COMMITTED каждый SELECT видит снимок на начало своей команды.
Поэтому второй SELECT видит уже зафиксированное изменение другого соединения.

При REPEATABLE READ снимок закрепляется первым обычным запросом транзакции.
Повторный SELECT продолжает видеть 10, хотя writer уже сохранил 20.
После COMMIT следующая транзакция сможет увидеть новое значение.

Для обмена нужна обычная таблица: TEMP-таблица другого соединения невидима.
SharedSchema создаёт отдельную схему `cpp_lab_<pid>` на запуск и удаляет её
при обычном выходе. Не прерывайте программу принудительно, если хотите
автоматическую уборку; после аварии схема может остаться в учебной базе.

READ COMMITTED — стандартный уровень PostgreSQL. SERIALIZABLE усиливает
гарантии, но может требовать повтора всей транзакции при SQLSTATE 40001.
Каждому параллельно используемому клиенту/потоку нужно своё PGconn.

[Изоляция](https://www.postgresql.org/docs/current/transaction-iso.html) ·
[libpq и потоки](https://www.postgresql.org/docs/current/libpq-threading.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 17
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 17
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
