# 04. SELECT, фильтрация и сортировка

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

SELECT читает выбранные столбцы, не изменяя таблицу.

~~~sql
SELECT name, price FROM products
WHERE price >= 50
ORDER BY price DESC, id
LIMIT 2;
~~~

WHERE оставляет подходящие строки. ORDER BY сортирует по убыванию цены,
а id разрешает совпадения цен. LIMIT возвращает первые две строки результата.

~~~text
Bag | 90
Book | 70
~~~

Без ORDER BY база не обещает постоянный порядок, даже если при нескольких
запусках он совпал. Для устойчивого разбиения на страницы сортировка должна
однозначно упорядочивать строки.

Пустая выборка — успешный запрос с PQntuples == 0, а не SQL-ошибка.
Перед обращением к ячейке нужно проверить существование строки.
В common/db.hpp функция value проверяет границы и отсутствие NULL.
Полученные через текстовый протокол числа ещё представлены строками.

[SELECT](https://www.postgresql.org/docs/current/sql-select.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 04
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 04
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
