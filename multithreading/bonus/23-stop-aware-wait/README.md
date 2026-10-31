# 23. Ожидание с поддержкой остановки

C++20; стандарт выбирается через cxx-standard.txt.
Продолжение [condition_variable](../04-condition-variable/)
и [jthread/stop_token](../06-jthread-stop-token/).

Рабочий поток может ждать данные сколько угодно долго. Нужно уметь закончить
это ожидание по запросу остановки, даже если данные так и не появятся.
Для этого используется перегрузка std::condition_variable_any:

~~~cpp
const bool received = cv.wait(lock, stop, [&]() { return ready; });
~~~

Обычная std::condition_variable не имеет этой перегрузки со stop_token.
condition_variable_any также допускает другие совместимые типы блокировок,
но в этом уроке используется знакомый unique_lock<mutex>.

## main.cpp: данных нет, поступает запрос остановки

1. Работник захватывает mtx и сообщает started.set_value(), что начал работу.
2. wait() проверяет ready, освобождает mtx на время ожидания и ждёт.
3. Главный поток вызывает worker.request_stop().
4. Ожидание, связанное с этим stop_token, получает уведомление об остановке.
5. Работник снова захватывает mtx, проверяет предикат и получает false:
   ready так и не изменился.
6. После lock.unlock() работник печатает результат и завершает функцию.
7. main ждёт полного завершения через join().

~~~text
Wait result: false
Stop requested: true
Worker finished without data
~~~

started/startSignal нужны для согласования начала примера без sleep_for().
Они не гарантируют, что работник уже физически заснул внутри wait().
Если request_stop() случится раньше входа в wait(), запрос всё равно
сохранится в состоянии stop_token, и ждать данные поток не будет.

Явного cv.notify_one() для этой остановки не требуется:
перегрузка с stop_token сама связывает ожидание с запросом остановки.
Для обычной condition_variable один request_stop() такого эффекта не даёт.

## main2.cpp: данные приходят обычным способом

main под mtx записывает message = 42, устанавливает ready = true,
освобождает mtx и вызывает cv.notify_one(). Запроса остановки в этом варианте нет:

~~~text
Wait result: true
Worker received: 42
~~~

Раннее уведомление не мешает: wait() проверит сохранённый ready.

## Что означает bool и зачем unique_lock

Возвращаемый bool — результат предиката:

- true: ready оказался true;
- false: ожидание остановлено, а ready остался false.

Если готовность и остановка совпали, true всё ещё возможен:
bool сам по себе не сообщает, поступал ли запрос остановки.
Это можно отдельно проверить через stop.stop_requested().

После возврата из wait() unique_lock снова владеет mtx в обоих случаях.
Чтение message защищено тем же мьютексом, что и запись.
lock.unlock() освобождает его перед независимым выводом.

request_stop() — кооперативный запрос, а не принудительное завершение потока.
Он не прерывает произвольную работу или обычный sleep_for().
Не вызывайте его под мьютексом, который может понадобиться обработчикам
остановки: такие обработчики могут выполняться синхронно в вызывающем потоке.

## Сборка и запуск

Откройте main.cpp или main2.cpp и нажмите F5 либо Ctrl+F5.
Из корня репозитория на Linux:

~~~bash
bash scripts/build-linux.sh multithreading/bonus/23-stop-aware-wait/main.cpp
./build/multithreading/bonus/23-stop-aware-wait/main
~~~

На Windows из MSYS2 Bash:

~~~bash
bash scripts/build-windows.sh multithreading/bonus/23-stop-aware-wait/main.cpp
./build/multithreading/bonus/23-stop-aware-wait/main.exe
~~~

Для получения данных замените main.cpp/main на main2.cpp/main2.
После добавления исходников обновите IntelliSense через задачу
C/C++: Update IntelliSense.

[Прерываемое ожидание в проекте стандарта](https://eel.is/c++draft/thread.condvarany.intwait).
[Все бонусы](../README.md).
