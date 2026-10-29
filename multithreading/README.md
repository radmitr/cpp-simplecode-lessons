# Многопоточность

Начните с уроков 01–10, затем переходите к [бонусам](bonus/README.md).
В каждой папке есть README с пояснением текущего кода.

## Основные уроки

1. [Потоки](lesson-01-thread/) — запуск и ожидание завершения.
2. [Аргументы потока](lesson-02-thread-param/) — передача значений.
3. [std::ref](lesson-03-std-ref/) — изменение исходной переменной.
4. [Лямбда](lesson-04-lambda/) — получение результата через захват по ссылке.
5. [Методы класса](lesson-05-class-methods/) — объект, его копия и ссылка.
6. [mutex](lesson-06-mutex/) — ручные lock/unlock.
7. [lock_guard](lesson-07-lock-guard/) — автоматическое освобождение.
8. [Deadlock](lesson-08-deadlock/) — порядок захвата двух мьютексов.
9. [recursive_mutex](lesson-09-recursive-mutex/) — повторный захват тем же потоком.
10. [unique_lock](lesson-10-unique-lock/) — отложенный захват и ручное освобождение.

## Бонусы

1. [atomic](bonus/01-atomic/) — общий счётчик и гонка данных.
2. [try_lock](bonus/02-try-lock/) — попытка захвата без ожидания и adopt_lock.
3. [scoped_lock](bonus/03-scoped-lock/) — захват пары мьютексов.
4. [condition_variable](bonus/04-condition-variable/) — wait, wait_for, wait_until, notify_one и notify_all.
5. [future и async](bonus/05-future-async/) — результат и исключение из задачи.
6. [jthread и stop_token](bonus/06-jthread-stop-token/) — остановка потока, C++20.
7. [semaphore](bonus/07-semaphore/) — acquire, release и ограничение числа одновременных пользователей, C++20.
8. [shared_mutex](bonus/08-shared-mutex/) — несколько читателей и исключительный доступ писателя.
9. [promise и future](bonus/09-promise-future/) — явная передача результата и исключения из std::thread.
10. [producer–consumer](bonus/10-producer-consumer/) — очередь заданий и корректное завершение потребителей.
11. [пул потоков](bonus/11-thread-pool/) — постоянные работники, очередь и future для каждой задачи.
12. [barrier](bonus/12-barrier/) — согласование повторяющихся этапов вычисления, C++20.

## Сборка и особенности

Откройте корень репозитория или папку отдельного урока в VS Code,
выберите нужный main*.cpp и нажмите F5. main.cpp, main2.cpp и другие
варианты — самостоятельные программы; вместе их собирать не нужно.
Сами папки multithreading/ и bonus/ конфигураций VS Code не содержат.

По умолчанию используется C++17. Бонусы jthread, semaphore и barrier используют C++20.
Подробные команды: [общий README](../README.md) и [скрипты сборки](../scripts/README.md).

Урок 02 намеренно не завершается из-за бесконечного цикла; остановите его
через Ctrl+C или остановку отладки. В остальных примерах порядок выполнения
потоков и время работы могут различаться между запусками. sleep_for изображает
работу и не гарантирует порядок выполнения. join ожидает поток, а mutex защищает
совместный доступ к данным — это разные задачи.
