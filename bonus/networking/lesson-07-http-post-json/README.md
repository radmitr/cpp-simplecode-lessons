# 07. HTTP POST с JSON

C++17. Windows: MinGW64; Linux: POSIX. Нужна libcurl с заголовками.

Клиент отправляет на /config тело {"value":42} с Content-Type: application/json.
Сервер проверяет путь, метод, тип содержимого и схему тела:

~~~text
HTTP status: 200
Body: {"accepted":true,"value":42}
~~~

libcurl получает указатель на тело и его длину в байтах.
Строка body существует до завершения curl_easy_perform(); передавать указатель
на уже уничтоженную временную строку нельзя.

Сервер не рассчитывает, что тело придёт вместе с заголовками одним recv():
сначала разбирает Content-Length, затем дочитывает ровно это количество байтов.
Длина больше 4096 отклоняется. Передача chunked не поддерживается.

http::parseValue() — ограниченный разбор только объекта с одним целым value.
Он отвергнет {"value":01}, строки вместо числа, лишние поля и переполнение int.
Для произвольного JSON используйте специализированную библиотеку.

Сервер не сохраняет настройки на диск.

Для проверки вручную можно отправить POST из отдельного терминала:

~~~bash
curl -i -H "Content-Type: application/json" --data '{"value":42}' http://127.0.0.1:42007/config
~~~

На Windows PowerShell удобнее использовать C++-клиент этого урока:
правила кавычек при передаче JSON внешней curl.exe зависят от версии PowerShell.
После каждого запроса учебный сервер нужно перезапускать.

## Сборка и запуск

Порт по умолчанию: 42007. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-07-http-post-json/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-07-http-post-json/client.cpp
~~~

Первый терминал:

~~~bash
./build/bonus/networking/lesson-07-http-post-json/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-07-http-post-json/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-07-http-post-json/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-07-http-post-json/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\bonus\networking\lesson-07-http-post-json\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-07-http-post-json\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на client.cpp.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
