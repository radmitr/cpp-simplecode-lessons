# Бонусы по основам C++

После основных типов, функций, указателей и классов из [курса](../README.md) читайте бонусы по номерам: типы и инициализация → время жизни и владение → операции с типами → константные вычисления и устройство программы → время и диагностика. Обобщённые пакеты привязок в конце требуют также знания шаблонов.

Номера папок задают порядок изучения внутри раздела. Уроки SimpleCode сохраняют исходную нумерацию.

## Уроки

- [01. Основные типы и sizeof на практике](01-fundamental-types/README.md) — `c++17`.
- [02. Инициализация и `initializer_list`](02-initialization/README.md) — `c++17`.
- [03. Числа, диапазоны и преобразования](03-numeric-conversions/README.md) — `c++17`.
- [04. Ссылки, `const` и время жизни](04-references-and-lifetime/README.md) — `c++17`.
- [05. `auto`, ссылки и `decltype(auto)`](05-auto-and-decltype/README.md) — `c++17`.
- [06. Структурированные привязки и псевдонимы](06-structured-bindings/README.md) — `c++17`.
- [07. `enum class` и битовые флаги](07-enum-class/README.md) — `c++17`.
- [08. Хранение C-строк и управляющие символы](08-c-strings-and-escapes/README.md) — `c++17`.
- [09. RAII: ресурс связан со временем жизни объекта](09-raii/README.md) — `c++17`.
- [10. Перемещение и `std::move`](10-move-semantics/README.md) — `c++17`.
- [11. Правило нуля, трёх и пяти](11-rule-of-zero-five/README.md) — `c++17`.
- [12. `unique_ptr`: фабрики, массивы и deleter](12-unique-ptr/README.md) — `c++17`.
- [13. `shared_ptr`, `weak_ptr` и циклы владения](13-shared-weak-ptr/README.md) — `c++17`.
- [14. Лямбды: время жизни и захват перемещением](14-lambda-lifetime/README.md) — `c++17`.
- [15. Вызываемые объекты, `invoke` и `reference_wrapper`](15-callables-and-invoke/README.md) — `c++17`.
- [16. Пользовательские литералы](16-user-defined-literals/README.md) — `c++17`.
- [17. Именованная инициализация агрегата](17-designated-initializers/README.md) — `c++20`.
- [18. Трёхстороннее сравнение](18-three-way-comparison/README.md) — `c++20`.
- [19. Вычисления во время компиляции: `constexpr` и `consteval`](19-constexpr-consteval/README.md) — `c++20`.
- [20. if `consteval` и явное копирование auto](20-consteval-and-auto-copy/README.md) — `c++23`.
- [21. ODR, `inline` и связывание](21-odr-and-linkage/README.md) — `c++17`.
- [22. Статические объекты и `constinit`](22-static-initialization/README.md) — `c++20`.
- [23. Скобки в функциональном макросе](23-macro-parentheses/README.md) — `c++17`.
- [24. Биты, `endian` и `bit_cast`](24-bits-and-representation/README.md) — `c++20`.
- [25. Перечисления и порядок байтов](25-enums-and-bytes/README.md) — `c++23`.
- [26. `chrono`: длительности и монотонные часы](26-chrono/README.md) — `c++17`.
- [27. Календарные даты и время суток](27-calendar/README.md) — `c++20`.
- [28. Часовые пояса и местное время](28-time-zones/README.md) — `c++20`.
- [29. Генераторы, распределения и воспроизводимость](29-random/README.md) — `c++17`.
- [30. Диагностика, `assert` и санитайзеры](30-diagnostics/README.md) — `c++17`.
- [31. Место вызова `source_location`](31-source-location/README.md) — `c++20`.
- [32. Трассировка стека вызовов](32-call-stack-trace/README.md) — `c++17`.
- [33. Предположения оптимизатору и недостижимый код](33-assume-and-unreachable/README.md) — `c++23`.
- [34. Вычисляемые сообщения и удалённые функции](34-compile-time-diagnostics/README.md) — `c++26`.
- [35. Пакеты структурированных привязок](35-structured-bindings-packs/README.md) — `c++26`.

## Как работать

Откройте корень проекта или папку урока и выберите нужный исходник.
[F5, Ctrl+F5 и команды терминала](../../README.md#сборка-и-запуск-в-vs-code).
В каждом README указаны ввод, результат, ошибки, зависимости и ограничения.
В списке выше дан **режим сборки**; даты появления отдельных возможностей объясняются в уроках.

[Учебный маршрут](../../docs/learning-path.md) · [Версии C++](../../docs/cpp-versions.md) · [Все уроки](../../LESSONS.md).

Проверка из корня проекта: `python3 scripts/check-bonuses.py --section basics/bonus`.
На Windows имя команды Python может быть `python`.
