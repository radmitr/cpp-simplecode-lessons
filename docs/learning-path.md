# Учебный маршрут

Порядок ниже задаётся зависимостями тем. Номер папки курса сохраняет номер
SimpleCode, номер бонуса обозначает порядок его добавления. Ни один из них
не обязан совпадать с годом стандарта или местом урока в учебном маршруте.

Для быстрого поиска по редакции языка используйте [указатель версий](cpp-versions.md),
для оценки глубины примеров — [карту покрытия](cpp-coverage.md).
Все ссылки ведут на существующие уроки; повторные копии программ для разных маршрутов не нужны.

## 1. Основы языка

Начните с [основ курса](../basics/README.md): переменные, выражения, ветвления,
циклы, функции, массивы, указатели и ссылки. Затем:

1. [Инициализация и списки](../basics/bonus/04-initialization/README.md).
2. [Числовые преобразования и границы](../basics/bonus/05-numeric-conversions/README.md).
3. [`auto`, `decltype` и ссылки](../basics/bonus/06-auto-and-decltype/README.md).
4. [`enum class` и флаги](../basics/bonus/07-enum-class/README.md).
5. [Пользовательские литералы](../basics/bonus/42-user-defined-literals/README.md).
6. [Вычисления `constexpr`/`consteval`](../basics/bonus/01-constexpr-consteval/README.md).

## 2. Время жизни и устройство типов

После [классов и конструкторов](../oop/README.md):

1. [RAII и ресурс](../basics/bonus/02-raii/README.md), [ссылки и время жизни](../basics/bonus/03-references-and-lifetime/README.md).
2. [Перемещение](../basics/bonus/09-move-semantics/README.md) и [правило нуля/пяти](../basics/bonus/10-rule-of-zero-five/README.md).
3. [Уникальное владение](../basics/bonus/11-unique-ptr/README.md), [разделяемое и слабое владение](../basics/bonus/12-shared-weak-ptr/README.md).
4. [Время жизни захватов лямбды](../basics/bonus/22-lambda-lifetime/README.md).
5. [Именованная инициализация агрегата](../basics/bonus/43-designated-initializers/README.md).
6. [Категории сравнения и `<=>`](../basics/bonus/40-three-way-comparison/README.md).

## 3. Шаблоны и ограничения

Идите по [бонусам шаблонов](../templates/bonus/README.md): вывод параметров →
специализация и CTAD → свойства типов и `if constexpr` → пакеты и свёртки →
`std::forward` → concepts и `requires`. В уроке параметров отдельно разобраны
[шаблоны переменных и последовательности индексов](../templates/bonus/17-template-parameters/README.md).

## 4. Контейнеры, строки и результаты

Сначала изучите [контейнеры и алгоритмы курса](../stl/README.md), затем:

1. [`string_view`](../stl/bonus/22-string-view/README.md) → [`span`](../stl/bonus/05-span/README.md) →
   [диапазоны и представления](../stl/bonus/06-ranges-and-views/README.md).
2. [`optional`](../stl/bonus/19-optional/README.md) → [`expected`](../stl/bonus/04-expected/README.md).
3. [`variant` и обработка альтернатив](../stl/bonus/20-variant/README.md) →
   [`any` и проверка точного типа](../stl/bonus/21-any/README.md).
4. [Перенос узлов](../stl/bonus/23-node-handles/README.md), затем
   [плоские контейнеры](../stl/bonus/08-flat-containers/README.md): это разные способы хранения.
5. [Ресурсы памяти `pmr`](../stl/bonus/24-memory-resources/README.md).
6. [`mdspan`](../stl/bonus/09-mdspan/README.md) → [линейная алгебра](../stl/bonus/18-linalg/README.md),
   с учётом доступности библиотечного API.

## 5. Ошибки, ввод-вывод и время

Идите по [исключениям](../exceptions/README.md) и [IO-бонусам](../io/bonus/README.md).
Сначала нужны состояние потока, строгий разбор чисел и проверка ошибок,
затем форматы, файловая система и сохранение данных.

После обычной диагностики изучите [место вызова](../basics/bonus/41-source-location/README.md)
и [стек вызовов](../io/bonus/24-stacktrace/README.md): они отвечают на разные вопросы.
После [длительностей и часов](../basics/bonus/27-chrono/README.md) переходите к
[календарным датам](../basics/bonus/44-calendar/README.md), затем к
[часовым поясам](../basics/bonus/45-time-zones/README.md).

## 6. Многопоточность и отложенное выполнение

Порядок в [разделе многопоточности](../multithreading/bonus/README.md):
потоки и `join` → мьютексы → ожидание по условию → `future` → остановка →
семафоры, барьеры и атомики. Таймауты разделяемого доступа показаны в
[`shared_timed_mutex`](../multithreading/bonus/08-shared-mutex/README.md).

Затем изучите [политики выполнения алгоритмов](../stl/bonus/25-parallel-algorithms/README.md).
После RAII можно отдельно пройти [корутины и генераторы](../bonus/coroutines/README.md).
После обоих направлений — [senders/receivers](../bonus/execution/README.md),
учитывая ограничения реализации C++26.

## 7. Устройство программы и дальнейшие дополнения

После заголовков и раздельной компиляции изучите [ODR](../basics/bonus/24-odr-and-linkage/README.md),
затем [модули](../bonus/modules/README.md). Для развития современных тем есть
[карта C++20–26](modern-cpp.md), [контракты](../bonus/contracts/README.md) и
[рефлексия](../bonus/reflection/README.md).

Практические направления — [сети](../bonus/networking/README.md) и
[PostgreSQL](../bonus/databases/postgresql/README.md) — требуют также знания
ошибок, времени жизни, IO и многопоточности. Их внешние библиотеки и службы
описаны в собственных инструкциях, а не определяются версией C++.
