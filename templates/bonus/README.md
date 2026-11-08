# Бонусы по шаблонам

После [шаблонов курса](../README.md) нужны функции, ссылки и классы. Порядок: вывод параметров → специализация и CTAD → свойства типов → пакеты → пробрасывание аргументов → ограничения → современные дополнения.

Номера папок задают порядок изучения внутри раздела. Уроки SimpleCode сохраняют исходную нумерацию.

## Уроки

- [01. Шаблоны функций и вывод параметров](01-function-templates/README.md) — `c++17`.
- [02. Параметры шаблонов, специализация и CTAD](02-template-parameters/README.md) — `c++17`.
- [03. `type_traits`, `if constexpr` и `enable_if`](03-traits-if-constexpr/README.md) — `c++17`.
- [04. Пакеты параметров и fold expressions](04-parameter-packs/README.md) — `c++17`.
- [05. Forwarding references и `std::forward`](05-perfect-forwarding/README.md) — `c++17`.
- [06. Concepts и `requires`](06-concepts/README.md) — `c++20`.
- [07. Перенос квалификаторов через forward_like](07-forward-like/README.md) — `c++23`.
- [08. Индексирование пакета параметров](08-pack-indexing/README.md) — `c++26`.

## Как работать

Откройте корень проекта или папку урока и выберите нужный исходник.
[F5, Ctrl+F5 и команды терминала](../../README.md#сборка-и-запуск-в-vs-code).
В каждом README указаны ввод, результат, ошибки, зависимости и ограничения.
В списке выше дан **режим сборки**; даты появления отдельных возможностей объясняются в уроках.

[Учебный маршрут](../../docs/learning-path.md) · [Версии C++](../../docs/cpp-versions.md) · [Все уроки](../../LESSONS.md).

Проверка из корня проекта: `python3 scripts/check-bonuses.py --section templates/bonus`.
На Windows имя команды Python может быть `python`.
