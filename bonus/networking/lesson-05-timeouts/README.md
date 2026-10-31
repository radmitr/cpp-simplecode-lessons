# 05. Неблокирующие сокеты, таймауты и ошибки

C++17. Windows: MinGW64; Linux: POSIX.

Сервер принимает строку Please reply, но намеренно не отвечает.
Клиент ждёт до своего deadline около 200 мс и обрабатывает net::Timeout:

~~~text
Expected timeout: no response within the deadline
~~~

После выхода из main клиент закрывает сокет через RAII.
Сервер узнаёт об этом по recv() == 0 и завершает работу.
Таймаут и закрытие соединения — разные события.

В common/net.hpp сокеты неблокирующие:
ioctlsocket(FIONBIO) на Windows, fcntl(O_NONBLOCK) на Linux.
Когда операция пока невозможна, API сообщает WSAEWOULDBLOCK либо
EAGAIN/EWOULDBLOCK. select() ждёт готовности, затем операция пробуется снова.
Готовность не отменяет проверку результата send()/recv().

Неблокирующий connect() может сообщить, что подключение ещё выполняется.
После готовности на запись нужно проверить getsockopt(SO_ERROR):
готовность сама по себе не доказывает успешного подключения.
Этот приём использован и в BladeClient из relays_manage.

Дедлайн основан на steady_clock. Повтор после EINTR или частичного обмена
использует прежний момент, поэтому таймаут не начинается заново.
Точное время возврата зависит также от планировщика.

Если сервер не запущен, клиент может получить отказ подключения либо
истечение дедлайна — это зависит от ОС и сетевых настроек.
Не делайте бесконечные быстрые повторные connect(): повторной попытке
нужны ограничение количества/времени и пауза. Этот пример завершает работу
с ошибкой; политику повторов приложение выбирает отдельно.

## Сборка и запуск

Порт по умолчанию: 42005. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-05-timeouts/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-05-timeouts/client.cpp
~~~

Первый терминал:

~~~bash
./build/bonus/networking/lesson-05-timeouts/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-05-timeouts/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-05-timeouts/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-05-timeouts/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\bonus\networking\lesson-05-timeouts\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-05-timeouts\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на client.cpp.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
