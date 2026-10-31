# 10. Фоновая отправка последнего значения

C++17. Windows: MinGW64; Linux: POSIX.

main публикует value=1, value=2 и value=3 через LatestSender::update().
Отдельный поток выполняет подключение и сетевую запись.
update() удерживает mutex только во время обновления строки и флага.

Как и в relays_manage, хранится последнее значение, а не очередь всех значений.
Если worker ещё не забрал value=1, новое value=2 может его заменить.
Поэтому сервер получит от одной до трёх строк, но последней должна быть value=3.

Работник использует знакомую конструкцию:

~~~cpp
changed_.wait(lock, [&]() { return stopped_ || pending_; });
~~~

Во время ожидания mutex свободен. После пробуждения worker снова владеет им,
забирает строку, сбрасывает pending_ и выходит из блока.
Сетевая операция выполняется уже после освобождения mutex.
main может тем временем публиковать новое значение.

finish() устанавливает stopped_, вызывает notify_one() и делает join().
Работник перед выходом отправляет оставшееся pending_-значение.
Только после join() main читает сохранённое исключение и при необходимости
повторно выбрасывает его. Деструктор тоже обеспечивает завершение, но не бросает
сетевое исключение: для его явной обработки вызовите finish().

Здесь используется одно TCP-соединение, в отличие от отдельного соединения
на сообщение в BladeClient. Переподключения и бесконечных повторов в уроке нет.
Их можно добавить следующим отдельным вариантом с явной политикой остановки.

Успешный sendAll() означает передачу байтов локальному TCP-стеку.
Подтверждения применения значения удалённой программой здесь нет.
Для него понадобился бы ответ ACK на уровне прикладного протокола.
Сервер читает строки до закрытия соединения и проверяет последнее значение.

## Сборка и запуск

Порт по умолчанию: 42010. Сначала соберите обе программы.
Linux, из корня репозитория:

~~~bash
bash scripts/build-linux.sh bonus/networking/lesson-10-background-sender/server.cpp
bash scripts/build-linux.sh bonus/networking/lesson-10-background-sender/client.cpp
~~~

Первый терминал:

~~~bash
./build/bonus/networking/lesson-10-background-sender/server
~~~

После строки Listening во втором терминале:

~~~bash
./build/bonus/networking/lesson-10-background-sender/client
~~~

Windows, PowerShell, из корня:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-10-background-sender/server.cpp
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh bonus/networking/lesson-10-background-sender/client.cpp
~~~

Первый терминал:

~~~powershell
& .\build\bonus\networking\lesson-10-background-sender\server.exe
~~~

После строки Listening во втором терминале:

~~~powershell
& .\build\bonus\networking\lesson-10-background-sender\client.exe
~~~

При открытии папки урока в VS Code доступны задачи Networking: Run server
и Networking: Run client. Сначала запустите сервер и дождитесь Listening.
Они сами соберут соответствующий исходник; программы запускаются отдельно.
Для отладки клиента оставьте сервер в терминале и нажмите F5 на client.cpp.

После добавления исходников выполните C/C++: Update IntelliSense.
[Общие настройки, зависимости и общий код](../README.md).
