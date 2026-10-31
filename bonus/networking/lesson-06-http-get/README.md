# 06. HTTP GET и ответ сервера

C++17. Windows: MinGW64; Linux: POSIX. Нужна libcurl с заголовками.

Клиент libcurl делает GET /hello. Локальный C++-сервер возвращает JSON:

~~~text
HTTP status: 200
Body: {"message":"Hello from HTTP"}
~~~

HTTP-запрос содержит метод, путь и версию, затем заголовки, пустую строку
и необязательное тело. Ответ содержит строку статуса, заголовки и тело.
В HTTP/1.x разделители строк — CRLF (\r\n).

В common/http.hpp сервер получает заголовки до пустой строки, затем читает
тело по Content-Length. Ответ содержит длину в байтах и Connection: close.
После ответа соединение закрывается. Полноценные keep-alive и chunked
в этом ограниченном учебном сервере не реализованы.

GET /missing вернёт 404; другой метод для этого сервера — 405 с Allow: GET.
CURLE_OK означает успешное выполнение обмена libcurl, но не обязательно
HTTP 200. HTTP-статус проверяется отдельно через CURLINFO_RESPONSE_CODE.

Клиент допускает URL первым аргументом. Например, для HTTP-порта 43006:

~~~text
http://127.0.0.1:43006/hello
~~~

Сервер обрабатывает один запрос, поэтому для новой проверки запустите его снова.
Таймаут соединения клиента — 1 с, всей операции — 3 с.
Тело ответа ограничено 64 КиБ. GET сам по себе не является REST API.

## Сборка и запуск

Порт по умолчанию: 42006. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-06-http-get/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-06-http-get/client.cpp
~~~

Первый терминал:

~~~bash
./build/bonus/networking/lesson-06-http-get/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-06-http-get/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-06-http-get/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-06-http-get/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\bonus\networking\lesson-06-http-get\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-06-http-get\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на client.cpp.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
