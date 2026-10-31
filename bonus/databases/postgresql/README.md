# PostgreSQL из C++: 20 уроков

C++17 · официальная клиентская библиотека libpq · Windows/MinGW64 и Linux.
Каждый урок — отдельная программа с README, комментариями и настройками VS Code.
Можно идти по порядку; каждый пример сам подготавливает свои данные.

PostgreSQL — система управления базами данных; postgres — также имя исполняемого
файла её сервера. psql — консольный клиент, libpq — библиотека для подключения
нашей программы к серверу. Установки одного компилятора для работы с БД недостаточно.

## Подготовка на Windows

В терминале **MSYS2 MinGW64**, не MSYS:

~~~bash
pacman -S --needed mingw-w64-x86_64-postgresql
~~~

Это пакет для компилятора из /mingw64: сервер, psql, libpq, заголовки и инструменты
резервного копирования. Пакет postgresql без префикса относится к среде MSYS;
для этих C++-примеров выбирается mingw-w64-x86_64-postgresql.
Если компилятор ещё не установлен:

~~~bash
pacman -S --needed mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb
~~~

В PowerShell Bash вызывают по пути C:\msys64\usr\bin\bash.exe.
Для прямого запуска .exe и F5 из корня проекта добавьте
C:\msys64\mingw64\bin в PATH и перезапустите VS Code.
Скрипт run.sh и локальные настройки уроков добавляют этот каталог сами.
Не смешивайте библиотеки MinGW64 с MSVC или другим окружением MSYS2.

## Подготовка на Linux

Ubuntu/Debian:

~~~bash
sudo apt install build-essential gdb postgresql postgresql-client libpq-dev openssl
~~~

Arch Linux:

~~~bash
sudo pacman -S --needed gcc gdb postgresql openssl
~~~

Нужны серверные initdb/pg_ctl, клиентские инструменты, заголовки и libpq.
Скрипт на Linux находит серверные утилиты через pg_config --bindir.
Для другой установки укажите PG_BIN с абсолютным путём к каталогу этих утилит.
Рекомендуется поддерживаемая версия PostgreSQL 14 или новее.
Примеры не используют возможности, специфичные только для версии 18.

Уже работающий системный PostgreSQL можно оставить: учебный экземпляр ниже
использует другой каталог и порт. Скрипт не обращается к системной службе.
initdb запускают от обычного пользователя, **без sudo**.

## Создание и запуск учебного сервера

Все команды — из корня репозитория. Linux / MSYS2 MinGW64:

~~~bash
bash bonus/databases/postgresql/scripts/lab.sh init
bash bonus/databases/postgresql/scripts/lab.sh start
bash bonus/databases/postgresql/scripts/run.sh 01
~~~

Windows PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/lab.sh init
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/lab.sh start
& C:\msys64\usr\bin\bash.exe bonus/databases/postgresql/scripts/run.sh 01
~~~

init выполняют один раз: он создаёт **кластер** — каталог экземпляра PostgreSQL,
а не одну таблицу. start запускает сервер и при необходимости создаёт базу
cpp_lessons. Повторные init/start не очищают данные.
run.sh 01 собирает и запускает первый урок; замените номер на 02…20.

По умолчанию используются:

- TCP-адрес 127.0.0.1, порт 55432; подключения извне компьютера не принимаются.
- Роль cpp_student и база cpp_lessons.
- .local/postgresql/data — данные; server.log — журнал.
- .local/postgresql/pgpass.conf — сгенерированный пароль.
  Вся папка .local/postgresql игнорируется Git, включая резервные копии.

Пароль создаётся случайно и не передаётся в командной строке.
Включена SCRAM-аутентификация. На Linux файл пароля имеет права 0600;
на Windows доступ определяется ACL каталога: храните его в личном рабочем каталоге.
Загрузочный пользователь cpp_student — суперпользователь **этого учебного кластера**.
Для настоящего приложения создают отдельную роль с минимальными правами;
учебные настройки не предназначены для публикации сервера в сети.

Если порт занят, задайте PGLESSONS_PORT перед init и используйте то же значение
при следующих запусках скриптов, программ и VS Code.
PGLESSONS_HOME позволяет выбрать другой абсолютный каталог данных и пароля;
на Windows используйте путь вида D:/pg-lab. Эти переменные наследуются программами.
При смене порта уже созданный кластер скрипт потребует согласовать с port.txt;
проще выбрать свободный порт до первой инициализации.

Управление, Linux / MSYS2:

~~~bash
bash bonus/databases/postgresql/scripts/lab.sh status
bash bonus/databases/postgresql/scripts/lab.sh psql
bash bonus/databases/postgresql/scripts/lab.sh stop
~~~

В PowerShell замените начальное bash на & C:\msys64\usr\bin\bash.exe.
В psql команды SQL заканчиваются точкой с запятой, `\dt` показывает таблицы,
`\q` завершает клиент. TEMP-таблицы программы C++ не видны в отдельном psql.
stop ждёт завершения сервера; данные сохраняются.
Автоматический запуск как Windows-служба или системная служба Linux не настраивается.

## Уроки

1. [Подключение и первый SELECT](lesson-01-connect/README.md).
2. [Таблицы, столбцы и типы](lesson-02-tables-types/README.md).
3. [INSERT и RETURNING](lesson-03-insert/README.md).
4. [SELECT, фильтрация и сортировка](lesson-04-select/README.md).
5. [UPDATE и DELETE](lesson-05-update-delete/README.md).
6. [Параметры и защита от SQL-инъекции](lesson-06-parameters/README.md).
7. [Подготовленные запросы](lesson-07-prepared-statements/README.md).
8. [NULL и пустая строка](lesson-08-null-values/README.md).
9. [Ограничения и SQLSTATE](lesson-09-constraints/README.md).
10. [Связи и JOIN](lesson-10-joins/README.md).
11. [Группировка и агрегатные функции](lesson-11-aggregation/README.md).
12. [Транзакции: COMMIT и ROLLBACK](lesson-12-transactions/README.md).
13. [Точки сохранения](lesson-13-savepoints/README.md).
14. [INSERT ON CONFLICT](lesson-14-upsert/README.md).
15. [Индексы и EXPLAIN](lesson-15-indexes/README.md).
16. [JSONB](lesson-16-jsonb/README.md).
17. [Изоляция и снимки данных](lesson-17-isolation/README.md).
18. [Блокировки строк и таймаут](lesson-18-row-locks/README.md).
19. [Массовая загрузка и выгрузка COPY](lesson-19-copy/README.md).
20. [Резервная копия и проверка восстановления](lesson-20-backup-restore/README.md).

## Как устроен код и запуск

SQL внутри R"(...)" выполняется сервером. C++ управляет соединением, параметрами,
результатами и ошибками. [common/db.hpp](common/db.hpp) содержит RAII-обёртки;
[их устройство](common/README.md) объясняет PGconn, PGresult, SQLSTATE и транзакции.
Используется libpq, поэтому отдельная C++-библиотека libpqxx не нужна.

В уроках 02–16 и 19 таблицы временные: закрытие соединения удаляет их.
В 17–18 нужна общая таблица для двух соединений; она создаётся в отдельной схеме
и убирается при обычном выходе. В 20 схема backup_demo постоянная для pg_dump.
Примеры не требуют результатов предыдущих уроков.

run.sh вызывает обычный build-windows.sh или build-linux.sh. Рядом с main.cpp
лежит link-libraries.txt с pq: сборка добавляет -lpq. На Debian/Ubuntu заголовок
находится в postgresql/libpq-fe.h; общий заголовок учитывает оба распространённых
расположения. При нестандартной установке настройте пути компилятора/линкера.
Результаты — build/bonus/databases/postgresql/lesson-…/main[.exe].

В VS Code откройте корень проекта или папку урока, затем main.cpp и нажмите F5.
Сервер нужно запустить заранее; F5 собирает и запускает **клиентскую программу**.
При добавлении исходников обновите задачу C/C++: Update IntelliSense.

Все примеры используют синхронные вызовы. Подключение ограничено 3 секундами,
обычный запрос — серверным statement_timeout в 5 секунд. Это учебные ограничения,
а не полный механизм сетевых дедлайнов и восстановления соединения.
Один PGconn нельзя одновременно использовать из нескольких потоков.

## Проверка

При запущенном учебном сервере тест собирает все 20 программ, проверяет вывод,
SQL-ошибки, работу блокировки, COPY и восстановление архива в отдельную базу.
Дополнительно проверяется отказ при неверном пароле и недоступном сервере.
Нужен Python 3.9+.

Linux / MSYS2:

~~~bash
python3 bonus/databases/postgresql/tests/smoke.py
~~~

Windows PowerShell:

~~~powershell
python bonus/databases/postgresql/tests/smoke.py
~~~

После проверки остановите учебный сервер командой lab.sh stop.
Восстановленные базы остаются для осмотра; их имена выводятся тестом.
Проверка не удаляет существующие базы.

## Частые ошибки

- Connection refused: сначала lab.sh start, затем проверьте порт.
- password authentication failed: используйте свой pgpass.conf и тот же
  PGLESSONS_HOME/PGLESSONS_PORT. Не публикуйте файл с паролем.
- libpq-fe.h not found / cannot find -lpq: установите пакет разработки
  для своего компилятора (на Debian/Ubuntu — libpq-dev).
- libpq.dll not found: добавьте MinGW64 bin в PATH.
- initdb: cannot be run as root: запускайте от обычного пользователя.
- Ошибка после обновления PostgreSQL на другую major-версию:
  старый каталог данных нельзя просто открыть новым сервером.
  Используйте подходящий сервер и dump/restore либо pg_upgrade.

[Документация PostgreSQL](https://www.postgresql.org/docs/current/) ·
[Пакет MSYS2](https://packages.msys2.org/packages/mingw-w64-x86_64-postgresql) ·
[Дополнительные направления](../../README.md).
