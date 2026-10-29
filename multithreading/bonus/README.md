# Бонусы по многопоточности

Дополнительные примеры после уроков 01–10. Рекомендуемый порядок:

1. [01-atomic](01-atomic/) — гонка данных, счётчик с mutex и atomic.
2. [02-try-lock](02-try-lock/) — попытка захвата без ожидания и метка adopt_lock.
3. [03-scoped-lock](03-scoped-lock/) — захват двух мьютексов.
4. [04-condition-variable](04-condition-variable/) — ожидание, таймауты и уведомления одного или всех потоков.
5. [05-future-async](05-future-async/) — результат и исключение из фоновой задачи.
6. [06-jthread-stop-token](06-jthread-stop-token/) — запрос остановки и автоматический join (C++20).

В каждом каталоге есть отдельный README и конфигурации VS Code. Можно открыть
корень проекта или отдельную папку бонуса, выбрать main.cpp и нажать F5.

Первые пять тем используют C++17. Для шестой общие скрипты сборки читают
cxx-standard.txt в папке исходника и выбирают C++20. Нужны компилятор и
стандартная библиотека с поддержкой std::jthread и std::stop_token.
Вывод примеров использует ASCII, поэтому настройка кодировки Windows не нужна.

Из корня репозитория на Linux:

~~~bash
bash scripts/build-linux.sh multithreading/bonus/01-atomic/main.cpp
./build/multithreading/bonus/01-atomic/main
~~~

На Windows из MSYS2 Bash:

~~~bash
bash scripts/build-windows.sh multithreading/bonus/01-atomic/main.cpp
./build/multithreading/bonus/01-atomic/main.exe
~~~

Подставьте путь к выбранной теме. Бинарники находятся в build/multithreading/bonus/.
