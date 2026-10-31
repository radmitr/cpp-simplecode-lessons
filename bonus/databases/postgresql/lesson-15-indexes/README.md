# 15. Индексы и EXPLAIN

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

Создаются 30 000 событий. Один и тот же поиск id = 23456 выполняется
до и после создания B-tree индекса events_id_idx.

~~~sql
EXPLAIN (ANALYZE, BUFFERS, COSTS OFF, TIMING OFF)
SELECT * FROM events WHERE id = 23456;
~~~

До индекса обычно виден Seq Scan — просмотр таблицы.
После обычно появляется Index Scan или Bitmap Index Scan.
Точный план, времена и число буферов зависят от версии и среды.

- EXPLAIN показывает выбранный план.
- ANALYZE внутри EXPLAIN действительно исполняет запрос.
  Для UPDATE/DELETE это означает реальные изменения.
- BUFFERS показывает работу с буферами. У TEMP-таблицы это local buffers.
- Отдельная команда ANALYZE обновляет статистику распределения данных.
  Для временных таблиц её особенно важно выполнять явно.

Индекс занимает место и увеличивает стоимость записи.
Планировщик может предпочесть Seq Scan для маленькой таблицы или выборки
большой доли строк. Пример не отключает Seq Scan искусственно и
проверяет результат поиска, а не точное название узла плана.

[EXPLAIN](https://www.postgresql.org/docs/current/using-explain.html) ·
[Индексы](https://www.postgresql.org/docs/current/indexes.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 15
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 15
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
