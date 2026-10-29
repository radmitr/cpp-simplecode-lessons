# Бонусы по многопоточности

Дополнительные примеры после уроков 01–10. Рекомендуемый порядок:

1. [01-atomic](01-atomic/) — гонка данных, счётчик с mutex и atomic.
2. [02-try-lock](02-try-lock/) — попытка захвата без ожидания и метка adopt_lock.
3. [03-scoped-lock](03-scoped-lock/) — захват двух мьютексов.
4. [04-condition-variable](04-condition-variable/) — ожидание, таймауты и уведомления одного или всех потоков.
5. [05-future-async](05-future-async/) — результат и исключение из фоновой задачи.
6. [06-jthread-stop-token](06-jthread-stop-token/) — запрос остановки и автоматический join (C++20).
7. [07-semaphore](07-semaphore/) — acquire, release и ограничение числа одновременных пользователей, C++20.
8. [08-shared-mutex](08-shared-mutex/) — несколько читателей и исключительный доступ писателя.
9. [09-promise-future](09-promise-future/) — явная передача результата и исключения из std::thread.
10. [10-producer-consumer](10-producer-consumer/) — очередь заданий и корректное завершение потребителей.
11. [11-thread-pool](11-thread-pool/) — постоянные работники, очередь и future для каждой задачи.
12. [12-barrier](12-barrier/) — согласование повторяющихся этапов вычисления, C++20.
13. [13-timed-mutex](13-timed-mutex/) — захват мьютекса с таймаутом.
14. [14-thread-local](14-thread-local/) — личная переменная каждого потока.
15. [15-osyncstream](15-osyncstream/) — цельные сообщения из нескольких потоков, C++20.
16. [16-atomic-wait](16-atomic-wait/) — ожидание атомарного значения и уведомления, C++20.
17. [17-memory-order](17-memory-order/) — relaxed и публикация данных через acquire/release.
18. [18-parallel-sum](18-parallel-sum/) — проверка результата и сравнение времени для разного числа потоков.

Дополнительные варианты существующих тем:
main2.cpp в [10-producer-consumer](10-producer-consumer/) ограничивает размер очереди,
а main2.cpp в [11-thread-pool](11-thread-pool/) отменяет ожидающие задания.

В каждом каталоге есть отдельный README и конфигурации VS Code. Можно открыть
корень проекта или отдельную папку бонуса, выбрать main.cpp и нажать F5.

Бонусы 06 (jthread), 07 (semaphore), 12 (barrier), 15 (osyncstream)
и 16 (atomic::wait) используют C++20, остальные — C++17. Общие скрипты читают cxx-standard.txt в папке исходника.
Нужны компилятор и стандартная библиотека с поддержкой используемых средств C++20.
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
