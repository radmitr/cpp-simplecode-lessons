# Версии C++: появление API и режим сборки

**«Появилось в C++20»** означает: возможность включили в эту редакцию стандарта.
**«Сборка C++23»** означает: компилятору выбран режим `-std=c++23`.
Код с `std::jthread` можно собрать в C++23, но `jthread` остаётся API из C++20.

В этом проекте режим по умолчанию — **C++17**. Файл `cxx-standard.txt` рядом
с исходником выбирает другой режим; `gcc-min-version.txt` может потребовать
более новый GCC. Подробности: [скрипты сборки](../scripts/README.md).
Компилятор и стандартная библиотека должны поддерживать нужный API:
одного принятого флага `-std` недостаточно.

## Краткий указатель

Ниже перечислены используемые здесь возможности, а не все изменения стандартов.

- **C++98**: основные типы, функции, классы, доступ, конструкторы/деструкторы,
  перегрузки, шаблоны, обычные ссылки, пространства имён, `try/throw/catch`,
  `new/delete`, `static_cast/dynamic_cast`, RTTI, `iostream`, `string`,
  `vector/list/deque/map/set`, адаптеры контейнеров и классические алгоритмы.
  `reserve`, `push_back`, `std::max`, `std::boolalpha` тоже не новые API.
- **C++03**: преимущественно уточнения C++98; в том числе формализация
  value-initialization. Не называйте весь «старый C++» C++17 только из-за сборки.
- **C++11**: `auto` с выводом типа, `decltype`, `nullptr`, `constexpr`,
  лямбды, `enum class`, range-for, rvalue-ссылки, `std::move/forward`,
  `= default/delete`, `noexcept`, списки инициализации, `initializer_list`,
  `unique_ptr/shared_ptr/weak_ptr`, `array`, unordered-контейнеры,
  `emplace/emplace_back`, `thread`, мьютексы, `lock_guard/unique_lock`,
  `condition_variable`, `atomic`, `future/promise/async/shared_future`,
  `chrono`, `random`, `function`, `reference_wrapper`, `system_error`.
- **C++14**: `make_unique`, обобщённые лямбды с `auto`-параметром,
  захват с инициализацией (например `[p = std::move(p)]`), `decltype(auto)`,
  `shared_timed_mutex`, расширения возможностей `constexpr`.
- **C++17**: структурированные привязки, `if constexpr`, fold expressions,
  CTAD (вывод параметров шаблона класса), inline-переменные,
  гарантированное исключение копии в определённых prvalue-сценариях,
  `optional/variant/any`, `string_view`, `filesystem`, `from_chars/to_chars`,
  `invoke/apply`, `scoped_lock/shared_mutex`.
- **C++20**: concepts и `requires`, `consteval` и `constinit`, `span`, ranges,
  `bit_cast/endian`, `format`, `jthread` и совместная остановка,
  `counting_semaphore/binary_semaphore`, `latch/barrier`, `osyncstream`,
  `atomic::wait/notify_one/notify_all`.
- **C++23**: `print/println`, `expected`, `std::to_underlying`,
  `if consteval` и другие новые API. Наличие GCC с C++23 не гарантирует
  поддержку всех функций его библиотекой.
- **C++26, экспериментально в этом проекте**: статическая рефлексия,
  `^^`, `std::meta::info` и связанные операции. Здесь используется конкретная
  реализация GCC с `-freflection`; требования и статус приведены в
  [разделе рефлексии](../bonus/reflection/README.md).
  Не переносите эти примеры в обычную сборку C++17/20 без изменений.

Функция `acquire()` семафора — C++20, а имя порядка атомарной памяти
`std::memory_order_acquire` — C++11. Совпадение слова не делает их одним API.
`join()` обычного потока — C++11, автоматическое ожидание `jthread` — C++20.

## Как читать пометки уроков

Раздел «Версия C++» отмечает ключевые возможности, которые фактически
использует код. В одном файле могут встречаться разные даты появления.
Комментарий `// C++20 — std::jthread.` относится к указанной возможности,
а не утверждает, что все строки файла требуют C++20.

Правила нуля, трёх и пяти, RAII, producer–consumer и пул потоков —
приёмы проектирования. У них нет собственной редакции стандарта;
версия определяется средствами конкретного примера.

WinSock, POSIX-сокеты, libcurl, Boost.Asio и libpq/PostgreSQL — внешние API.
У них свои версии и требования, которые нельзя обозначить как «часть C++17».
Режим C++ относится к окружающему исходнику, а зависимости указаны отдельно.

## Проверка поддержки

Смотрите версию компилятора (`g++ --version`), выбранный режим и доступность
заголовков/feature-test macros. Значение `__cplusplus` отражает выбранный
режим, а не полную реализацию всех возможностей.
Для отдельного API применяются макросы вида `__cpp_lib_jthread`
из `<version>`; их значения и контракт сверяйте с документацией.

[Статус libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html)
и [перечень стандартов ISO C++](https://isocpp.org/std/the-standard)
помогают проверить поддержку. [Другие источники](references.md).
