# 08. Ресурсный HTTP API

C++17. Windows: MinGW64; Linux: POSIX. Нужна libcurl с заголовками.

Локальный сервер хранит элементы в std::map<int, int>.
Каждый элемент имеет id и целочисленный value.
Клиент последовательно выполняет пять запросов:

~~~text
POST /items -> 201 {"id":1,"value":42}
GET /items/1 -> 200 {"id":1,"value":42}
PUT /items/1 -> 200 {"id":1,"value":7}
DELETE /items/1 -> 204
GET /items/1 -> 404 {"error":"not found"}
~~~

POST создаёт ресурс, присваивает id и возвращает Location.
GET читает представление, PUT заменяет value, DELETE удаляет элемент.
204 означает успешное выполнение без тела ответа.
После удаления GET получает 404.

Транспортные ошибки libcurl и HTTP 4xx/5xx различаются: запрос мог успешно
дойти до сервера, а сервер вернуть ошибку. Клиент проверяет и статус, и тело.
Все пять проверок ожидают свежий сервер с пустой map.

Это учебный API в стиле REST с ресурсами и HTTP-методами.
Он не демонстрирует все ограничения REST, включая гипермедиа.
JSON не является обязательным форматом для REST; здесь он выбран для наглядности.

Сервер последователен, обрабатывает ровно пять соединений и завершается.
Данные существуют только в памяти. Авторизация, маршрутизация общего назначения
и полноценный JSON-парсер в этом уроке не добавлены.

Клиенту можно передать базовый URL, например http://127.0.0.1:43008
без завершающего /. Для ручных запросов потребуется учесть лимит пяти обращений.

## Сборка и запуск

Порт по умолчанию: 42008. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-08-rest-api/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-08-rest-api/client.cpp
~~~

Первый терминал:

~~~bash
./build/bonus/networking/lesson-08-rest-api/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-08-rest-api/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-08-rest-api/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-08-rest-api/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\bonus\networking\lesson-08-rest-api\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-08-rest-api\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на client.cpp.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
