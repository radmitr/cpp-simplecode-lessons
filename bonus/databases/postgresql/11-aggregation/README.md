# 11. Группировка и агрегатные функции

## Версия C++

`auto`, лямбды — **C++11**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.
libpq/PostgreSQL — внешняя зависимость со своей версией; версия C++ относится к клиентскому исходнику.

## Что изучаем

`GROUP` BY объединяет строки по категории. `count` считает строки группы,
`sum` складывает суммы. HAVING отбирает группы по агрегированному результату.

## Примеры

- [main.cpp](main.cpp).

Выбирайте один исходник с `main()`; варианты запускаются отдельно.

## Как это работает

~~~sql
SELECT category, count(*) AS items, sum(amount) AS total
FROM sales
WHERE amount > 0
GROUP BY category
HAVING sum(amount) >= 150
ORDER BY total DESC, category;
~~~

~~~text
books | 2 | 300
~~~

`WHERE` применяется к отдельным строкам до группировки.
HAVING проверяется для сформированных групп: у games сумма 120, поэтому
эта группа не попадает в вывод.

`count(*)` считает строки, `count(column)` — только непустые значения столбца.
`sum` на пустом наборе возвращает `NULL`; при необходимости используйте
`COALESCE(sum(amount), 0)`. Выбранный неагрегированный столбец обычно должен
участвовать в `GROUP` BY.

[Агрегатные функции](https://www.postgresql.org/docs/current/functions-aggregate.html).

## Сборка и запуск

[Запуск в VS Code](../../../../README.md#сборка-и-запуск-в-vs-code).

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают `main.cpp` и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 11
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 11
~~~

В VS Code откройте `main.cpp` и нажмите F5/Ctrl+F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).

## Связанные темы и источники

[Версии C++](../../../../docs/cpp-versions.md) · [Как читать справочники](../../../../docs/references.md).
