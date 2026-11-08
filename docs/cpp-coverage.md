# Карта покрытия возможностей C++

Это проверяемый указатель основных учебных тем, а не перечень всех пунктов ISO C++.
Статус относится к **указанному сценарию**, а не ко всем перегрузкам и возможным
пользовательским типам. Упоминание API в тексте или случайный вызов в другом уроке
само по себе не означает полноценного разбора.

- **Разобрано** — есть целевой исходник, объяснение механизма, запуска и ограничений.
- **Частично** — применение есть, но отдельные важные сценарии ещё не разобраны.
- **Нет примера** — нужен самостоятельный учебный материал.
- **Подготовлено** — код есть, но основной API недоступен в используемой библиотеке;
  запуск ветки `UNAVAILABLE` не доказывает работоспособность основного сценария.

За последовательностью обучения обращайтесь к [учебному маршруту](learning-path.md).
Режим сборки и дата появления возможности различаются: [пояснение версий](cpp-versions.md).

## C++98 и C++03

| Тема | Статус и материал |
|---|---|
| Типы, выражения, условия, циклы, функции, массивы, указатели | Разобрано: [основы курса](../basics/README.md) |
| Ссылки, `const`, время жизни | Разобрано: [ссылки и объекты](../basics/additions/04-references-and-lifetime/README.md) |
| Классы, наследование, виртуальные функции | Разобрано: [ООП](../oop/README.md) |
| Ресурсы и копирование | Разобрано: [RAII](../basics/additions/09-raii/README.md), [копирование и перемещение](../basics/additions/11-rule-of-zero-five/README.md) |
| Шаблоны, специализация | Разобрано: [шаблоны](../templates/additions/README.md) |
| Основные контейнеры и алгоритмы | Разобрано: [STL](../stl/README.md) |
| Потоки, файлы, исключения | Разобрано: [IO](../io/README.md), [исключения](../exceptions/README.md) |
| Locale facets, `valarray`, пользовательские аллокаторы общего назначения | Нет отдельных уроков; `pmr` ниже не заменяет все требования Allocator |

C++03 преимущественно уточняет C++98; отдельной группы новых крупных механизмов
здесь не выделяется. Инициализация значением рассматривается в
[уроке инициализации](../basics/additions/02-initialization/README.md).

## C++11

| Тема | Статус и материал |
|---|---|
| `auto`, `decltype` | Разобрано: [вывод типа](../basics/additions/05-auto-and-decltype/README.md) |
| Лямбды, захваты | Разобрано: [жизнь захваченных объектов](../basics/additions/14-lambda-lifetime/README.md) |
| Rvalue-ссылки, `move`, `forward` | Разобрано: [перемещение](../basics/additions/10-move-semantics/README.md), [пробрасывание](../templates/additions/05-perfect-forwarding/README.md) |
| `unique_ptr`, `shared_ptr`, `weak_ptr` | Разобрано: [уникальное](../basics/additions/12-unique-ptr/README.md) и [разделяемое владение](../basics/additions/13-shared-weak-ptr/README.md) |
| Списки инициализации, `enum class` | Разобрано: [инициализация](../basics/additions/02-initialization/README.md), [перечисления](../basics/additions/07-enum-class/README.md) |
| `constexpr`, `noexcept` | Разобрано: [константные вычисления](../basics/additions/19-constexpr-consteval/README.md), [исключительность](../exceptions/additions/03-noexcept/README.md) |
| Пакеты параметров, псевдонимы, свойства типов | Разобрано: [дополнения шаблонов](../templates/additions/README.md) |
| Пользовательские литералы | Разобрано: [числовой и строковый суффикс](../basics/additions/16-user-defined-literals/README.md) |
| Потоки, мьютексы, атомики, `future` | Разобрано: [многопоточность](../multithreading/additions/README.md) |
| `chrono`, `random` | Разобрано: [часы](../basics/additions/26-chrono/README.md), [генератор и распределение](../basics/additions/29-random/README.md) |
| `regex`, unordered-контейнеры, `tuple` | Частично: [разбор HTTP](../additions/networking/README.md), [исключения стандартных типов](../exceptions/additions/01-exception-types/README.md), [структура в tuple](../additions/reflection/26-struct-to-tuple/README.md) |

## C++14

| Тема | Статус и материал |
|---|---|
| `make_unique` | Разобрано: [фабрика и массив](../basics/additions/12-unique-ptr/README.md) |
| Обобщённые лямбды, захват с инициализацией | Разобрано: [лямбды](../basics/additions/14-lambda-lifetime/README.md) |
| `decltype(auto)` | Разобрано: [ссылка или копия](../basics/additions/05-auto-and-decltype/README.md) |
| Шаблоны переменных, последовательности индексов | Разобрано: [параметры шаблонов, `main2.cpp`](../templates/additions/02-template-parameters/README.md) |
| `shared_timed_mutex`, таймаут общего доступа | Разобрано: [разделяемый мьютекс, `main3.cpp`](../multithreading/additions/07-shared-mutex/README.md) |
| Расширенные `constexpr`, стандартные строковые/временные литералы | Частично: [вычисления](../basics/additions/19-constexpr-consteval/README.md), [длительности](../basics/additions/26-chrono/README.md) |
| Бинарные литералы и разделители цифр | Частично: [биты](../basics/additions/24-bits-and-representation/README.md); отдельного сравнения синтаксиса нет |

## C++17

| Тема | Статус и материал |
|---|---|
| Структурированные привязки | Разобрано: [копии и ссылки](../basics/additions/06-structured-bindings/README.md) |
| `if constexpr`, CTAD, свёртки | Разобрано: [дополнения шаблонов](../templates/additions/README.md) |
| `optional`, `variant`, `any` | Разобрано: [наличие](../stl/additions/06-optional/README.md), [альтернатива](../stl/additions/08-variant/README.md), [точный тип](../stl/additions/09-any/README.md) |
| `string_view` | Разобрано: [представление и владелец](../stl/additions/04-string-view/README.md) |
| `filesystem`, `from_chars`/`to_chars` | Разобрано: [пути](../io/additions/13-filesystem-path/README.md), [операции](../io/additions/14-filesystem-operations/README.md), [числа](../io/additions/03-charconv/README.md) |
| Узлы `map`/`set`, `extract`, `merge` | Разобрано: [перенос и конфликт ключей](../stl/additions/14-node-handles/README.md) |
| PMR | Разобрано: [арена, пул и выбор аллокатора](../stl/additions/20-memory-resources/README.md) |
| Политики выполнения алгоритмов | Разобрано: [политики и свёртки](../stl/additions/21-parallel-algorithms/README.md); реальная параллельность зависит от backend |
| `scoped_lock`, `shared_mutex` | Разобрано: [несколько мьютексов](../multithreading/additions/06-scoped-lock/README.md), [читатели и писатель](../multithreading/additions/07-shared-mutex/README.md) |
| Inline-переменные, гарантированное исключение копии | Частично: [статические поля](../oop/lesson-092-oop-static-class-members/README.md), [правила специальных функций](../basics/additions/11-rule-of-zero-five/README.md) |
| `std::byte`, `invoke` | Разобрано: [представление числа](../basics/additions/24-bits-and-representation/README.md), [вызов](../basics/additions/15-callables-and-invoke/README.md) |

## C++20

| Тема | Статус и материал |
|---|---|
| Concepts и `requires` | Разобрано: [ограничения](../templates/additions/06-concepts/README.md) |
| `<=>`, категории сравнения | Разобрано: [сильный, слабый и частичный порядок](../basics/additions/18-three-way-comparison/README.md) |
| Designated initializers | Разобрано: [агрегат с именованными полями](../basics/additions/17-designated-initializers/README.md) |
| `consteval`, `constinit`, `bit_cast`, `endian` | Разобрано: [вычисления](../basics/additions/19-constexpr-consteval/README.md), [статика](../basics/additions/22-static-initialization/README.md), [биты](../basics/additions/24-bits-and-representation/README.md) |
| `span`, ranges | Разобрано: [массив](../stl/additions/05-span/README.md), [представления](../stl/additions/11-ranges-and-views/README.md) |
| Корутины | Разобрано: [кадр, awaiter, результаты, исключения, время жизни, отмена и другой поток](../additions/coroutines/README.md); промышленный async-runtime не реализован |
| `jthread`, остановка, семафоры, барьер, latch, `atomic::wait`, `osyncstream` | Разобрано: [дополнения многопоточности](../multithreading/additions/README.md) |
| `format`, `source_location` | Разобрано: [форматирование](../io/additions/05-format-and-print/README.md), [место вызова](../basics/additions/31-source-location/README.md) |
| Календарь и часовые пояса | Разобрано: [даты](../basics/additions/27-calendar/README.md), [переходы времени](../basics/additions/28-time-zones/README.md); для поясов нужна tzdata |
| Именованные модули | Разобрано: [интерфейс, повторный экспорт, разделы, global fragment и header units](../additions/modules/README.md); `import std` появился в C++23 и разобран отдельно |
| `char8_t` и UTF-8 | Разобрано: [байты и валидация](../io/additions/15-utf8/README.md); нормализация Unicode не реализована |
| `atomic_ref`, константные контейнеры, полный набор целочисленных функций `<bit>`, структурные параметры шаблона | Нет отдельных целевых примеров |

## C++23 и C++26

Подробные ссылки даёт [карта современных дополнений](modern-cpp.md).
Проверяемые примеры `expected`, `print`, адаптеров ranges, `mdspan`, генератора,
контрактов и рефлексии существуют. Это покрытие выбранных механизмов, а не всех
изменений языка и стандартной библиотеки.

`hive`, `linalg` и senders/receivers имеют статус **подготовлено** для установленной
libstdc++ 16.2.0: основной API отсутствует, проверяется только явный отказ с кодом `77`.
Работающий [внешний профиль](../additions/execution/reference-libraries.md)
отдельно проверяет закреплённые stdexec, stdBLAS/mdspan и plf::hive. Это не проверка
нативных стандартных API; совместимость и различия указаны рядом с примерами.

[Контракты](../additions/contracts/README.md) включают режимы проверки, обработчик,
порядок событий, исключения и инварианты. [Execution](../additions/execution/README.md)
включает состояние операции, receiver, завершения, композицию и переключение
планировщика; мост к корутинам явно использует внешний `stdexec::task`.

## Как дополнять карту

Сначала прочитайте исходники и все независимые `main`-варианты, затем уточняйте
статус. Новая тема добавляется в соответствующий `additions/`, связанные сценарии —
в существующий дополнение. Ссылки в учебном маршруте и указателе версий обновляются
в той же правке; перенумеровывать исходный курс для этого не требуется.

Наличие флага `-std` и успешный поиск имени API по исходникам не доказывают полноту
объяснения или поддержку всех вариантов. Точные контракты и версии сверяются с
[перечнем языка GCC](https://gcc.gnu.org/projects/cxx-status.html) и
[перечнем libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html).
