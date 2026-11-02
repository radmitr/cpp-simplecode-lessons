# Бонусы по многопоточности

Дополнительные примеры после уроков [«01. Запуск потоков»](../lesson-01-thread/README.md) — [«10. `std::unique_lock`: отложенный и повторный захват»](../lesson-10-unique-lock/README.md). Рекомендуемый порядок:

1. [«01. Гонка данных и `std::atomic`»](01-atomic/) — гонка данных, счётчик с `mutex` и `atomic`.
2. [«02. `std::mutex::try_lock`»](02-try-lock/) — попытка захвата без ожидания, `adopt_lock` и вариант с `try_to_lock`.
3. [«03. `std::scoped_lock`»](03-scoped-lock/) — захват двух мьютексов.
4. [«04. `std::condition_variable`»](04-condition-variable/) — ожидание с предикатом и без него, таймауты и уведомления одного или всех потоков.
5. [«05. `std::future` и `std::async`: запуск, ожидание и исключения»](05-future-async/) — десять программ: результат, исключение,
   `wait`, таймауты, `async`/`deferred`, время жизни и `terminate`.
6. [«06. `std::jthread` и `std::stop_token`»](06-jthread-stop-token/) — шесть программ: запрос, автоматический `join`, `joinable`, общий `stop_source` и `stop_callback` (C++20).
7. [«07. Семафор: `std::counting_semaphore`»](07-semaphore/) — пять программ: парковка, сигнал, `vector<jthread>`, таймауты и успешный `try_acquire` (C++20).
8. [«08. `std::shared_mutex` и `std::shared_lock`»](08-shared-mutex/) — несколько читателей, писатель и повторная проверка после смены режима.
9. [«09. `std::promise` и `std::future`»](09-promise-future/) — передача результата и исключения,
   отличие готовности от завершения потока и ошибки `promise`.
10. [«10. Очередь `producer`–consumer»](10-producer-consumer/) — очередь заданий и корректное завершение потребителей.
11. [«11. Учебный пул потоков»](11-thread-pool/) — постоянные работники, очередь и `future` для каждой задачи.
12. [«12. `std::barrier`»](12-barrier/) — четыре варианта: этапы, функция завершения, выход участника и токен прибытия, C++20.
13. [«13. `std::timed_mutex`»](13-timed-mutex/) — захват мьютекса с таймаутом.
14. [«14. `thread_local`»](14-thread-local/) — личная переменная, её деструктор и сохранение между заданиями пула.
15. [«15. `std::osyncstream`»](15-osyncstream/) — цельные сообщения, явный `emit` и управление сбросом, C++20.
16. [«16. `atomic::wait` и уведомления»](16-atomic-wait/) — ожидание атомарного значения и уведомления, C++20.
17. [«17. Порядки памяти: `relaxed`, `acquire` и `release`»](17-memory-order/) — `relaxed` и публикация данных через `acquire`/`release`.
18. [«18. Число потоков и время вычисления»](18-parallel-sum/) — проверка результата и сравнение времени для разного числа потоков.
19. [«19. Владение `std::unique_lock`: перемещение и освобождение»](19-unique-lock-move/) — перемещение владения, `release` и сравнение моментов захвата.
20. [«20. `std::call_once` и `std::once_flag`»](20-call-once/) — однократная инициализация и повторная попытка после исключения.
21. [«21. `std::latch`»](21-latch/) — одноразовый отсчёт, `arrive_and_wait` и `try_wait`, C++20.
22. [«22. `std::shared_future`»](22-shared-future/) — один результат или исключение для нескольких потребителей.
23. [«23. Ожидание с поддержкой остановки»](23-stop-aware-wait/) — ожидание данных с поддержкой `stop_token`, C++20.
24. [«24. compare_exchange: сравнить и заменить»](24-compare-exchange/) — атомарная условная замена, strong и цикл weak.
25. [«25. False sharing»](25-false-sharing/) — влияние расположения независимых счётчиков на производительность.
26. [«26. Поиск гонки данных с ThreadSanitizer»](26-thread-sanitizer/) — поиск гонки данных и проверка исправления на Linux/WSL.
27. [«27. Копия объекта, `std::ref` и лямбда»](27-class-method-arguments/) — копия, `std::ref`/`std::cref`, лямбда и удержание через `shared_ptr`; после урока [«05. Методы класса в потоке»](../lesson-05-class-methods/README.md).

Дополнительные варианты существующих тем:
`main2.cpp` в [«10. Очередь `producer`–consumer»](10-producer-consumer/) ограничивает размер очереди,
а `main2.cpp` в [«11. Учебный пул потоков»](11-thread-pool/) отменяет ожидающие задания.

В каждом каталоге есть отдельный README и конфигурации VS Code. Откройте
корень проекта или папку бонуса, выберите нужный `main*.cpp`.
**F5** запускает с отладчиком, **Ctrl+F5** — без отладчика.

Бонусы [«06. `std::jthread` и `std::stop_token`»](06-jthread-stop-token/README.md) (`jthread`), 07 (semaphore), 12 (barrier), 15 (osyncstream),
16 (`atomic::wait`), 21 (latch) и 23 (ожидание с остановкой) используют C++20,
остальные — C++17. Общие скрипты читают `cxx-standard.txt` в папке исходника.
Нужны компилятор и стандартная библиотека с поддержкой используемых средств C++20.
Вывод примеров использует ASCII, поэтому настройка кодировки Windows не нужна.

Для сравнения времени в [параллельной сумме](18-parallel-sum/README.md)
и [ложном разделении кэша](25-false-sharing/README.md) используйте оптимизированную сборку
из их README. В [Поиск гонки данных с ThreadSanitizer](26-thread-sanitizer/README.md) обычный F5/Ctrl+F5 не включает ThreadSanitizer:
для диагностики нужна отдельная задача или `run-tsan.sh` на Linux/WSL.
В [`std::call_once` и `std::once_flag`](20-call-once/README.md) `main2.cpp` пропускает эксперимент с исключением на MinGW/libstdc++:
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
