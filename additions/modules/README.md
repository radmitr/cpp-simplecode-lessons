# Модули C++

Нужны заголовки, ODR и раздельная компиляция. Порядок: интерфейс и реализация → несколько модулей и шаблоны → разделы и global module fragment → header units → стандартный модуль. Скрипт строит зависимости по manifest и пересоздаёт CMI; учебная конфигурация — GCC 16+. Ограничения GCC, включая private module fragment, отмечены в уроках.

## Уроки

- [01. Интерфейс и реализация модуля](01-interface-and-implementation/README.md) — `c++20`.
- [02. Несколько модулей, повторный экспорт и шаблоны](02-reexport-and-templates/README.md) — `c++20`.
- [03. Разделы модуля и global module fragment](03-partitions-and-global-fragment/README.md) — `c++20`.
- [04. Header units и макросы](04-header-units/README.md) — `c++20`.
- [05. Стандартный модуль и пересоздание CMI](05-import-std/README.md) — `c++23`.

[Учебный маршрут](../../docs/learning-path.md) · [Версии и покрытие](../../docs/cpp-coverage.md).

Проверка порядка сборки и CMI: `python3 scripts/check-modules.py` из корня проекта.
