# Бонусы по многопоточности

Дополнительные примеры после уроков 01–10. Рекомендуемый порядок:

1. [01-atomic](01-atomic/) — гонка данных, счётчик с mutex и atomic.
2. [02-try-lock](02-try-lock/) — попытка захвата без ожидания, adopt_lock и вариант с try_to_lock.
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
19. [19-unique-lock-move](19-unique-lock-move/) — передача владения unique_lock между функциями при оформлении заказа.
20. [20-call-once](20-call-once/) — однократная инициализация и повторная попытка после исключения.
21. [21-latch](21-latch/) — одноразовый отсчёт до готовности нескольких результатов, C++20.
22. [22-shared-future](22-shared-future/) — один результат или исключение для нескольких потребителей.
23. [23-stop-aware-wait](23-stop-aware-wait/) — ожидание данных с поддержкой stop_token, C++20.
24. [24-compare-exchange](24-compare-exchange/) — атомарная условная замена, strong и цикл weak.
25. [25-false-sharing](25-false-sharing/) — влияние расположения независимых счётчиков на производительность.
26. [26-thread-sanitizer](26-thread-sanitizer/) — поиск гонки данных и проверка исправления на Linux/WSL.

Дополнительные варианты существующих тем:
main2.cpp в [10-producer-consumer](10-producer-consumer/) ограничивает размер очереди,
а main2.cpp в [11-thread-pool](11-thread-pool/) отменяет ожидающие задания.

В каждом каталоге есть отдельный README и конфигурации VS Code. Можно открыть
корень проекта или отдельную папку бонуса, выбрать main.cpp и нажать F5.

Бонусы 06 (jthread), 07 (semaphore), 12 (barrier), 15 (osyncstream),
16 (atomic::wait), 21 (latch) и 23 (ожидание с остановкой) используют C++20,
остальные — C++17. Общие скрипты читают cxx-standard.txt в папке исходника.
Нужны компилятор и стандартная библиотека с поддержкой используемых средств C++20.
Вывод примеров использует ASCII, поэтому настройка кодировки Windows не нужна.

Для сравнения времени в бонусах 18 и 25 используйте оптимизированную сборку
из их README. В бонусе 26 обычный F5 не включает ThreadSanitizer:
для диагностики нужна отдельная задача или run-tsan.sh на Linux/WSL.
В бонусе 20 main2.cpp пропускает эксперимент с исключением на MinGW/libstdc++:
подробности ограничения и требуемое стандартом поведение описаны в его README.

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
