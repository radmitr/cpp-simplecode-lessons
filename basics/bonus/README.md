# Бонусы по основам C++

29 дополнений по основам: время жизни, владение, типы и диагностика.
Внутри крупных тем сначала изучайте время жизни и RAII, затем перемещение
и владение. Начните с [вычислений `constexpr` и `consteval`](01-constexpr-consteval/README.md)
и [связи ресурса со временем жизни объекта](02-raii/README.md).
Большинство уроков используют C++17; новые дополнения отмечены C++20/23/26.
Обычным урокам достаточно GCC 11+, современные выбирают GCC 16+.
Полная рефлексия вынесена отдельно в [bonus/reflection](../../bonus/reflection/README.md).

## Уроки

1. [constexpr и consteval](01-constexpr-consteval/README.md) — `c++20`.
2. [RAII и время жизни ресурсов](02-raii/README.md) — `c++17`.
3. [Ссылки, const и время жизни](03-references-and-lifetime/README.md) — `c++17`.
4. [Инициализация и initializer_list](04-initialization/README.md) — `c++17`.
5. [Числа, диапазоны и преобразования](05-numeric-conversions/README.md) — `c++17`.
6. [auto, ссылки и decltype(auto)](06-auto-and-decltype/README.md) — `c++17`.
7. [enum class и битовые флаги](07-enum-class/README.md) — `c++17`.
8. [Структурированные привязки и псевдонимы](08-structured-bindings/README.md) — `c++17`.
9. [Перемещение и std::move](09-move-semantics/README.md) — `c++17`.
10. [Правило нуля, трёх и пяти](10-rule-of-zero-five/README.md) — `c++17`.
11. [unique_ptr: фабрики, массивы и deleter](11-unique-ptr/README.md) — `c++17`.
12. [shared_ptr, weak_ptr и циклы владения](12-shared-weak-ptr/README.md) — `c++17`.
22. [Лямбды: время жизни и захват перемещением](22-lambda-lifetime/README.md) — `c++17`.
23. [Вызываемые объекты, invoke и reference_wrapper](23-callables-and-invoke/README.md) — `c++17`.
24. [ODR, inline и связывание](24-odr-and-linkage/README.md) — `c++17`.
25. [Статические объекты и constinit](25-static-initialization/README.md) — `c++20`.
26. [Биты, endian и bit_cast](26-bits-and-representation/README.md) — `c++20`.
27. [chrono: длительности и монотонные часы](27-chrono/README.md) — `c++17`.
28. [Генераторы, распределения и воспроизводимость](28-random/README.md) — `c++17`.
29. [Диагностика, assert и санитайзеры](29-diagnostics/README.md) — `c++17`.
31. [Основные типы и `sizeof` на практике](31-fundamental-types/README.md) — `c++17`.
32. [Трассировка стека вызовов](32-call-stack-trace/README.md) — `c++17`.
33. [Хранение C-строк и управляющие символы](33-c-strings-and-escapes/README.md) — `c++17`.
34. [Скобки в функциональном макросе](34-macro-parentheses/README.md) — `c++17`.

В этом списке указан **режим сборки**, а не дата появления каждой возможности.
Точные версии отдельных API даны в уроках; [указатель версий](../../docs/cpp-versions.md).
Порядок исключений: [уроки и бонусы раздела](../../exceptions/README.md).

## Как работать

Открывайте нужный `main.cpp` и нажимайте F5/Ctrl+F5. Каждый урок имеет локальные задачи
Windows/Linux и использует общие скрипты из корня репозитория. Обычные уроки
выбирают системный GCC, современные — `CXX_MODERN`; версии и зависимости
обозначены отдельно. Сборка всех примеров и проверка результатов:

```bash
python3 scripts/check-bonuses.py --section basics/bonus
```

На Windows вместо python3 можно использовать python; запускайте из корня.
Проверки создают временные данные только в `build/` и не меняют учебные файлы.

## Дополнительно

В уроке [«24. ODR, `inline` и связывание»](24-odr-and-linkage/README.md) открывайте `src/main.cpp`: он собирается вместе с `support.cpp`.
Отрицательные примеры не выполняются обычным F5/Ctrl+F5. ASan-проверка урока [«29. Диагностика, `assert` и санитайзеры»](29-diagnostics/README.md)
выделена в `run-sanitizers.sh` и требует Linux/WSL с установленной поддержкой.
Все основные примеры используют ASCII-вывод без перенастройки консоли.
Контейнеры, `std::optional`, `std::variant`, `std::string_view`, `std::span` и ranges подробно изучаются
в разделе STL; здесь библиотечные типы служат иллюстрациями механизмов языка.

[Бонусы шаблонов](../../templates/bonus/README.md) · [Бонусы исключений](../../exceptions/bonus/README.md).

## Дополнения современных стандартов

- [if consteval и явное копирование auto](35-consteval-and-auto-copy/README.md) — `c++23`.
- [Перечисления и порядок байтов](36-enums-and-bytes/README.md) — `c++23`.
- [Предположения оптимизатору и недостижимый код](37-assume-and-unreachable/README.md) — `c++23`.
- [Вычисляемые сообщения и удалённые функции](38-compile-time-diagnostics/README.md) — `c++26`.
- [Пакеты структурированных привязок](39-structured-bindings-packs/README.md) — `c++26`.

[Порядок изучения и карта тем](../../docs/modern-cpp.md). Требования и команды находятся в README каждого урока.
