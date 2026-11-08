# 05. `UPDATE` и `DELETE`

## Версия C++

`auto`, лямбды — **C++11**.
`std::string` — **C++98**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.
libpq/PostgreSQL — внешняя зависимость со своей версией; версия C++ относится к клиентскому исходнику.

## Что изучаем

`UPDATE` меняет существующие строки, `DELETE` удаляет их.
`WHERE` определяет, какие именно записи затронуть.

## Примеры

- [main.cpp](main.cpp).

Выбирайте один исходник с `main()`; варианты запускаются отдельно.

## Как это работает

~~~sql
UPDATE tasks SET done = true WHERE id = 1 RETURNING id, done;
DELETE FROM tasks WHERE done = true RETURNING title;
~~~

Без `WHERE` обновление или удаление затронет все строки таблицы.
В примере удаляется только завершённая задача, а затем выполняется
`DELETE` с несуществующим id.

~~~text
1 | t
Deleted: 1
Missing id affected: 0
~~~

`PQcmdTuples` возвращает текстовое число затронутых строк. Ноль означает,
что подходящих записей не было; это нормальный результат.
`RETURNING` позволяет получить изменённые/удалённые данные без второго запроса.

Это изменения данных, а DROP TABLE удаляет саму таблицу вместе со структурой.
Если несколько изменений должны либо сохраниться вместе, либо полностью
отмениться, нужна транзакция — урок [«12. Транзакции: `COMMIT` и `ROLLBACK`»](../12-transactions/README.md).

[UPDATE](https://www.postgresql.org/docs/current/sql-update.html) ·
[DELETE](https://www.postgresql.org/docs/current/sql-delete.html).

## Сборка и запуск

[Запуск в VS Code](../../../../README.md#сборка-и-запуск-в-vs-code).

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают `main.cpp` и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash additions/databases/postgresql/scripts/run.sh 05
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe additions/databases/postgresql/scripts/run.sh 05
~~~

В VS Code откройте `main.cpp` и нажмите F5/Ctrl+F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).

## Связанные темы и источники

[Версии C++](../../../../docs/cpp-versions.md) · [Как читать справочники](../../../../docs/references.md).
