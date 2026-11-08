# STL: контейнеры, итераторы и алгоритмы

Нужны циклы, ссылки, шаблоны типов и лямбды. Уроки сохраняют нумерацию исходного курса;
пропуски номеров не означают потерю файлов.

STL связывает контейнеры и алгоритмы через итераторы.
Сначала изучайте `vector` и диапазоны (01–02), затем остальные контейнеры
и адаптеры (03–12), потом алгоритмы (13–24).

## Как читать вызов алгоритма

Диапазон `[first, last)` включает `first` и не включает `last`.
`end()` обозначает позицию после последнего элемента, его нельзя разыменовывать.
Алгоритм получает позиции, поэтому сам по себе не всегда знает размер
или умеет увеличивать контейнер назначения.

- `find`/`max_element` возвращают позицию, а не `bool` или готовую копию значения.
- `copy` требует существующего назначения либо вставляющего итератора.
- `remove`/`unique` меняют логический диапазон; размер `vector` уменьшает `erase`.
- `sort` требует произвольного доступа и корректного строгого сравнения.
- Числовой init в `accumulate` задаёт тип аккумулятора.
- Часть операций инвалидирует сохранённые позиции. Проверяйте это до их повторного использования.

## Частые вопросы и продолжение

`reserve` не создаёт элементы; `map[key]` может создать запись; `list::remove`
и `std::remove` делают разную работу; `queue::pop` возвращает `void`.
В README уроков приведены значения, по которым это можно проследить.
Урок `09/main.cpp` ждёт ввод целого числа; урок `24/main.cpp` содержит
`random_shuffle`, удалённый из C++17. Современная альтернатива — `shuffle`.

Далее изучайте [строковое представление](bonus/22-string-view/README.md),
[представление массива](bonus/05-span/README.md),
[необязательное значение](bonus/19-optional/README.md),
[альтернативы типов](bonus/20-variant/README.md) и
[диапазоны](bonus/06-ranges-and-views/README.md).
Их время жизни, правила доступа и ограничения объясняются в отдельных уроках.

## Дополнения вне курса

[Бонусы по STL](bonus/README.md): инициализация `array`, тип аккумулятора
`accumulate`, различие круглых и фигурных скобок у `vector`.
Новые самостоятельные примеры находятся в `stl/bonus/`.

## Карта уроков

- [01. std::vector: размер, ёмкость и элементы](lesson-01-stl-vector/README.md).
- [02. Итераторы и полуоткрытый диапазон](lesson-02-stl-iterators/README.md).
- [03. std::list: двусвязный список](lesson-03-stl-list/README.md).
- [04. Префиксное и постфиксное продвижение итератора](lesson-04-stl-iterators-prefix-postfix/README.md).
- [05. std::forward_list: односвязный список](lesson-05-stl-forward-list/README.md).
- [06. std::array: фиксированный размер](lesson-06-stl-array/README.md).
- [07. Сравнение контейнеров](lesson-07-stl-containers-comparison-operators/README.md).
- [08. std::deque: доступ с двух концов](lesson-08-stl-deque/README.md).
- [09. std::set и std::multiset](lesson-09-stl-set-multiset/README.md).
- [10. std::map и std::multimap](lesson-10-stl-map-multimap/README.md).
- [11. std::stack: адаптер LIFO](lesson-11-stl-stack-container-adapter/README.md).
- [12. Очередь FIFO и очередь приоритетов](lesson-12-stl-queue-priority-queue-adapters/README.md).
- [13. Сортировка и бинарный предикат](lesson-13-stl-sorting-algorithms-binary-predicate-lambda/README.md).
- [14. Поиск: find, find_if и find_if_not](lesson-14-stl-find-algorithms/README.md).
- [15. Копирование и фильтрация](lesson-15-stl-copy-algorithms/README.md).
- [16. remove и физическое удаление](lesson-16-stl-remove-algorithms/README.md).
- [17. Поиск максимального элемента](lesson-17-stl-max-element/README.md).
- [18. Минимум и пара minmax_element](lesson-18-stl-min-element/README.md).
- [19. std::accumulate и тип аккумулятора](lesson-19-stl-accumulate/README.md).
- [20. equal и mismatch: границы двух диапазонов](lesson-20-stl-equal-mismatch-comparison/README.md).
- [21. Сравнение диапазонов с предикатом](lesson-21-stl-equal-with-predicate/README.md).
- [22. std::for_each и ссылки на элементы](lesson-22-stl-for-each-algorithm/README.md).
- [23. unique и unique_copy](lesson-23-stl-unique-algorithm/README.md).
- [24. Перемешивание и владение объектами](lesson-24-stl-random-shuffle/README.md).

## Сборка и запуск

Откройте корень проекта или отдельную папку урока в VS Code и выберите
нужный `main*.cpp`. **F5** запускает с отладчиком, **Ctrl+F5** — без отладчика.
Все `main`-варианты самостоятельные;
их не объединяют в одну программу. Используется C++17.

Из корня, Linux:

~~~bash
bash scripts/build-linux.sh 'stl/lesson-01-stl-vector/main.cpp'
./build/stl/lesson-01-stl-vector/main
~~~

Windows, PowerShell:

~~~powershell
& C:\msys64\usr\bin\bash.exe scripts/build-windows.sh 'stl/lesson-01-stl-vector/main.cpp'
& './build/stl/lesson-01-stl-vector/main.exe'
~~~

Заменяйте путь на нужный исходник. Папки со скобками и имена с пробелами
передавайте в кавычках. [Компиляторы и GDB](../README.md#требования) ·
[Устройство сборки](../scripts/README.md) · [Все уроки](../LESSONS.md).

## Курс и источники

[STL: vector, урок 1 и плейлист](https://www.youtube.com/watch?v=1cKvMZOJeeE&list=PLQOaTSbfxUtDWAtIYme5MLZ1l0GTyUYkB).
[Версии C++](../docs/cpp-versions.md) · [Справочники](../docs/references.md).

[Результат или ошибка: `std::expected`, C++23](bonus/04-expected/README.md)
дополняет работу с типами результатов и исключениями.
