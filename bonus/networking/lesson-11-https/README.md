# 11. HTTPS и проверка сертификата

C++17. Windows: MinGW64; Linux: POSIX. Нужна libcurl с заголовками.

main.cpp выполняет HTTPS GET через libcurl. По умолчанию запрашивается
https://example.com/. Можно передать другой HTTPS URL первым аргументом.

libcurl выполняет установку TCP/TLS-соединения, проверку цепочки сертификатов
и соответствия имени из URL сертификату. В common/curl_client.hpp явно включены:

~~~cpp
curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 1L);
curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 2L);
~~~

HTTPS шифрует обмен и позволяет проверить сторону соединения.
Отключать проверку ради исчезновения ошибки сертификата не нужно:
следует настроить доверенный CA или исправить имя сервера.

Вторым аргументом можно передать PEM-файл доверенного CA.
Это полезно для локального учебного сервера с собственным сертификатом.
Файл задаётся через CURLOPT_CAINFO; проверка имени при этом остаётся включённой.

Ожидается HTTP 200. Программа печатает статус и количество байтов, не всё тело.
Наличие доступа в Интернет, доверенных сертификатов и особенности proxy
зависят от окружения. Переданный URL должен начинаться с https://.
Скачивание ответа ограничено 64 КиБ, всей операции — тремя секундами.

Локальная проверка tests/smoke.py не обращается к example.com.
Она создаёт временный сертификат для localhost, поднимает Python TLS-сервер
и проверяет успешный запрос с доверенным CA, отказ без этого CA и отказ
при несовпадении имени. OpenSSL используется только для создания тестового
сертификата. Сам C++-клиент использует установленную libcurl с TLS-поддержкой.

[Проверка имени libcurl](https://curl.se/libcurl/c/CURLOPT_SSL_VERIFYHOST.html).
[Проверка сертификата libcurl](https://curl.se/libcurl/c/CURLOPT_SSL_VERIFYPEER.html).

## Сборка и запуск

Из корня репозитория на Linux:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-11-https/main.cpp
./build/bonus/networking/lesson-11-https/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-11-https/main.cpp
& .\build\bonus\networking\lesson-11-https\main.exe
~~~

Откройте main.cpp для запуска через F5/Ctrl+F5.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
