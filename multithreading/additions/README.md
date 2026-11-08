# Дополнения по многопоточности

Сначала пройдите [запуск потоков, мьютексы и управление захватом из курса](../README.md). Затем: передача объектов и локальные данные → владение захватом → ожидание и очереди → результаты и пул → остановка → средства координации → атомики → вывод и измерения. Дополнительный вариант про `thread_local` в пуле читайте после урока пула потоков.

Номера папок задают порядок изучения внутри раздела. Уроки SimpleCode сохраняют исходную нумерацию.

## Уроки

- [01. Копия объекта, `std::ref` и лямбда](01-class-method-arguments/README.md) — `c++17`.
- [02. `thread_local`](02-thread-local/README.md) — `c++17`.
- [03. Владение `std::unique_lock`: перемещение и освобождение](03-unique-lock-move/README.md) — `c++17`.
- [04. `std::mutex::try_lock`](04-try-lock/README.md) — `c++17`.
- [05. `std::timed_mutex`](05-timed-mutex/README.md) — `c++17`.
- [06. `std::scoped_lock`](06-scoped-lock/README.md) — `c++17`.
- [07. `std::shared_mutex` и `std::shared_lock`](07-shared-mutex/README.md) — `c++17`.
- [08. `std::call_once` и `std::once_flag`](08-call-once/README.md) — `c++17`.
- [09. `std::condition_variable`](09-condition-variable/README.md) — `c++17`.
- [10. Очередь `producer`–consumer](10-producer-consumer/README.md) — `c++17`.
- [11. `std::promise` и `std::future`](11-promise-future/README.md) — `c++17`.
- [12. `std::future` и `std::async`: запуск, ожидание и исключения](12-future-async/README.md) — `c++17`.
- [13. `std::shared_future`](13-shared-future/README.md) — `c++17`.
- [14. Учебный пул потоков](14-thread-pool/README.md) — `c++17`.
- [15. `std::jthread` и `std::stop_token`](15-jthread-stop-token/README.md) — `c++20`.
- [16. Ожидание с поддержкой остановки](16-stop-aware-wait/README.md) — `c++20`.
- [17. Семафор: `std::counting_semaphore`](17-semaphore/README.md) — `c++20`.
- [18. `std::latch`](18-latch/README.md) — `c++20`.
- [19. `std::barrier`](19-barrier/README.md) — `c++20`.
- [20. Гонка данных и `std::atomic`](20-atomic/README.md) — `c++17`.
- [21. Порядки памяти: `relaxed`, `acquire` и `release`](21-memory-order/README.md) — `c++17`.
- [22. compare_exchange: сравнить и заменить](22-compare-exchange/README.md) — `c++17`.
- [23. `atomic::wait` и уведомления](23-atomic-wait/README.md) — `c++20`.
- [24. `std::osyncstream`](24-osyncstream/README.md) — `c++20`.
- [25. Число потоков и время вычисления](25-parallel-sum/README.md) — `c++17`.
- [26. False sharing](26-false-sharing/README.md) — `c++17`.
- [27. Поиск гонки данных с ThreadSanitizer](27-thread-sanitizer/README.md) — `c++17`.

## Как работать

Откройте корень проекта или папку урока и выберите нужный исходник.
[F5, Ctrl+F5 и команды терминала](../../README.md#сборка-и-запуск-в-vs-code).
В каждом README указаны ввод, результат, ошибки, зависимости и ограничения.
В списке выше дан **режим сборки**; даты появления отдельных возможностей объясняются в уроках.

[Учебный маршрут](../../docs/learning-path.md) · [Версии C++](../../docs/cpp-versions.md) · [Все уроки](../../LESSONS.md).

Для измерений используйте оптимизированные команды из README уроков суммы и false sharing.
Обычный F5 не включает ThreadSanitizer: в его уроке есть отдельная задача и `run-tsan.sh`.
Вывод основных примеров использует ASCII. Ограничение MinGW для варианта `call_once`
с исключением описано в соответствующем README.
