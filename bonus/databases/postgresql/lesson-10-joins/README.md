# 10. Связи и JOIN

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

Один клиент может иметь несколько заказов: это связь «один ко многим».
orders.customer_id ссылается на customers.id через внешний ключ REFERENCES.

INNER JOIN возвращает только совпавшие пары. LEFT JOIN сохраняет также клиентов
без заказов; столбцы заказа у них равны NULL.

~~~text
INNER JOIN:
Alice | 10 | 100
Alice | 11 | 200
LEFT JOIN:
Alice | 10
Alice | 11
Bob | NULL
Foreign key rejected: 23503
~~~

ON задаёт условие соединения. c и o — короткие псевдонимы таблиц.
Внешний ключ не разрешает заказ для несуществующего клиента 999.
По умолчанию он также препятствует удалению клиента, на которого ссылаются заказы.
ON DELETE CASCADE используют только когда удаление дочерних записей
действительно соответствует смыслу данных.

Связь «многие ко многим» оформляют отдельной таблицей связей с двумя внешними
ключами и уникальной парой ключей. Сам JOIN не создаёт ограничения целостности.

[Соединения таблиц](https://www.postgresql.org/docs/current/queries-table-expressions.html).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 10
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 10
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
