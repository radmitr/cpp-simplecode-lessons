# 18. Блокировки строк и таймаут

C++17 · PostgreSQL · libpq · Windows/MinGW64 и Linux.

Первое соединение начинает транзакцию и выполняет SELECT ... FOR UPDATE.
Оно удерживает блокировку выбранной строки до COMMIT/ROLLBACK.

Второе соединение сначала делает обычный SELECT: он читает зафиксированную
версию строки без ожидания этой блокировки. Затем пытается выполнить UPDATE.

~~~text
Plain SELECT: 10
Contender timed out: 55P03
Retry after COMMIT: 11
~~~

SET LOCAL lock_timeout = '200ms' ограничивает ожидание блокировки только
в текущей транзакции. Пример не зависнет: UPDATE получит lock_not_available.
Ошибка обрабатывается после выхода из блока Transaction, который делает
ROLLBACK неудачной транзакции.

После COMMIT владельца повторный UPDATE проходит. Прибавление n = n + 1
выполняется самой базой; клиент не делает ненадёжное чтение и последующую
запись вычисленного заранее значения.

Блокировка строки не равна блокировке всей таблицы.
При захвате нескольких строк соблюдайте согласованный порядок;
иначе возможен deadlock (40P01). NOWAIT сразу сообщает о занятой строке,
а SKIP LOCKED пропускает её; это другие режимы, здесь демонстрируется ожидание.
Уровень изоляции и блокировка решают разные части задачи.

[Блокировки](https://www.postgresql.org/docs/current/explicit-locking.html) ·
[lock_timeout](https://www.postgresql.org/docs/current/runtime-config-client.html#GUC-LOCK-TIMEOUT).

## Сборка и запуск

Сначала [установите зависимости и запустите учебный сервер](../README.md).
Команды из корня репозитория собирают main.cpp и запускают результат.

Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/run.sh 18
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 18
~~~

В VS Code откройте main.cpp и нажмите F5. Сервер должен быть запущен заранее.
[Общий код и RAII](../common/README.md) · [Все 20 уроков](../README.md).
