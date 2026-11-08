# 17. Ресурсный HTTP API

## Версия C++

`std::from_chars` — **C++17**.
`std::chrono`, `std::to_string`, `auto` — **C++11**.
`std::string`, `std::runtime_error`, `std::map`, `std::exception` — **C++98**.

Сборка примеров: **C++17**. Это режим проекта,
а не дата появления всех использованных конструкций.
WinSock/POSIX-сокеты и libcurl — внешние API, не части стандарта C++.

## Что изучаем

Локальный сервер хранит элементы в `std::map<int, int>`.
Каждый элемент имеет `id` и целочисленный `value`.
Клиент последовательно выполняет пять запросов:

Windows: MinGW64; Linux: POSIX. Нужна libcurl с заголовками.

## Примеры

- [client.cpp](client.cpp).
- [server.cpp](server.cpp).

Сервер и клиент — две отдельные программы. Нужны обе: сначала сервер
в одном терминале, затем клиент в другом. Каждый исходник собирается отдельно.

## Как это работает

~~~text
POST /items -> 201 {"id":1,"value":42}
GET /items/1 -> 200 {"id":1,"value":42}
PUT /items/1 -> 200 {"id":1,"value":7}
DELETE /items/1 -> 204
GET /items/1 -> 404 {"error":"not found"}
~~~

POST создаёт ресурс, присваивает `id` и возвращает Location.
GET читает представление, PUT заменяет `value`, `DELETE` удаляет элемент.
204 означает успешное выполнение без тела ответа.
После удаления GET получает 404.

Транспортные ошибки libcurl и HTTP 4xx/5xx различаются: запрос мог успешно
дойти до сервера, а сервер вернуть ошибку. Клиент проверяет и статус, и тело.
Все пять проверок ожидают свежий сервер с пустой `map`.

Это учебный API в стиле REST с ресурсами и HTTP-методами.
Он не демонстрирует все ограничения REST, включая гипермедиа.
JSON не является обязательным форматом для REST; здесь он выбран для наглядности.

Сервер последователен, обрабатывает ровно пять соединений и завершается.
Данные существуют только в памяти. Авторизация, маршрутизация общего назначения
и полноценный JSON-парсер в этом уроке не добавлены.

Клиенту можно передать базовый URL, например http://127.0.0.1:43008
без завершающего /. Для ручных запросов потребуется учесть лимит пяти обращений.

## Сборка и запуск

[Запуск в VS Code](../../../README.md#сборка-и-запуск-в-vs-code).

Порт по умолчанию: 42008. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh additions/networking/17-rest-api/server.cpp
bash scripts/build-linux.sh additions/networking/17-rest-api/client.cpp
~~~

Первый терминал:

~~~bash
./build/additions/networking/17-rest-api/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/additions/networking/17-rest-api/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/17-rest-api/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh additions/networking/17-rest-api/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\additions\networking\17-rest-api\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\additions\networking\17-rest-api\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run `client`. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на `client.cpp`.
Для запуска без отладки используйте Ctrl+F5.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).

## Связанные темы и источники

### Дополнительные API в коде

- [Преобразование чисел через charconv](../../../io/additions/03-charconv/README.md): [полный пример](../../../io/additions/03-charconv/main.cpp).

[Версии C++](../../../docs/cpp-versions.md) · [Как читать справочники](../../../docs/references.md).
