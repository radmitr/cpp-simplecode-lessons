# 14. INSERT ON CONFLICT

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

Upsert добавляет новую строку или обновляет существующую при конфликте
уникальности. PRIMARY KEY(sku) определяет, что считается тем же товаром.

~~~sql
INSERT INTO inventory(sku, quantity) VALUES ($1::text, $2::int)
ON CONFLICT (sku) DO UPDATE
SET quantity = inventory.quantity + EXCLUDED.quantity
RETURNING sku, quantity;
~~~

EXCLUDED — предложенная для вставки строка, inventory — существующая.
Первый вызов добавляет 2, второй увеличивает количество ещё на 3.

~~~text
book | 2
book | 5
DO NOTHING affected: 0
~~~

DO NOTHING пропускает конфликтующую вставку. Это удобно, когда обновление
не требуется. Другие ограничения, например CHECK, всё ещё проверяются.

Один ON CONFLICT надёжнее схемы «сначала SELECT, потом INSERT»:
между двумя отдельными запросами другой клиент может вставить ту же запись.
При этом повтор прибавляющего upsert ещё раз увеличит значение —
идемпотентность не появляется автоматически.

[ON CONFLICT](https://www.postgresql.org/docs/current/sql-insert.html#SQL-ON-CONFLICT).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 14
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 14
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
