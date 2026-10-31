# Бонусы по основам C++

29 дополнений к исходному курсу: от времени жизни до ограничений шаблонов.
Уроки 01–02 сохраняют прежние примеры. Внутри крупных тем сначала изучайте
время жизни и RAII, затем перемещение/владение, исключения и шаблоны.
Большинство уроков используют C++17; отдельные возможности помечены C++20.
Примеры подобраны под GCC 11+, но фактический запуск Ubuntu ещё предстоит проверить.
Полная рефлексия вынесена отдельно в [bonus/reflection](../../bonus/reflection/README.md).

## Уроки

1. [constexpr и consteval](01-constexpr-consteval/README.md) — c++20.
2. [RAII и время жизни ресурсов](02-raii/README.md) — c++17.
3. [Ссылки, const и время жизни](03-references-and-lifetime/README.md) — c++17.
4. [Инициализация и initializer_list](04-initialization/README.md) — c++17.
5. [Числа, диапазоны и преобразования](05-numeric-conversions/README.md) — c++17.
6. [auto, ссылки и decltype(auto)](06-auto-and-decltype/README.md) — c++17.
7. [enum class и битовые флаги](07-enum-class/README.md) — c++17.
8. [Структурированные привязки и псевдонимы](08-structured-bindings/README.md) — c++17.
9. [Перемещение и std::move](09-move-semantics/README.md) — c++17.
10. [Правило нуля, специальные функции и возврат](10-rule-of-zero-five/README.md) — c++17.
11. [unique_ptr: фабрики, массивы и deleter](11-unique-ptr/README.md) — c++17.
12. [shared_ptr, weak_ptr и циклы владения](12-shared-weak-ptr/README.md) — c++17.
13. [Повторное выбрасывание и вложенные исключения](13-rethrow-and-nested/README.md) — c++17.
14. [noexcept, деструкторы и перемещение](14-noexcept/README.md) — c++17.
15. [Гарантии безопасности исключений](15-exception-guarantees/README.md) — c++17.
16. [Шаблоны функций и вывод параметров](16-function-templates/README.md) — c++17.
17. [Параметры шаблонов, специализация и CTAD](17-template-parameters/README.md) — c++17.
18. [type_traits, if constexpr и enable_if](18-traits-if-constexpr/README.md) — c++17.
19. [Пакеты параметров и fold expressions](19-parameter-packs/README.md) — c++17.
20. [Forwarding references и std::forward](20-perfect-forwarding/README.md) — c++17.
21. [Concepts и requires](21-concepts/README.md) — c++20.
22. [Лямбды: время жизни и захват перемещением](22-lambda-lifetime/README.md) — c++17.
23. [Вызываемые объекты, invoke и reference_wrapper](23-callables-and-invoke/README.md) — c++17.
24. [ODR, inline и связывание](24-odr-and-linkage/README.md) — c++17.
25. [Статические объекты и constinit](25-static-initialization/README.md) — c++20.
26. [Биты, endian и bit_cast](26-bits-and-representation/README.md) — c++20.
27. [chrono: длительности и монотонные часы](27-chrono/README.md) — c++17.
28. [Генераторы, распределения и воспроизводимость](28-random/README.md) — c++17.
29. [Диагностика, assert и санитайзеры](29-diagnostics/README.md) — c++17.

## Как работать

Открывайте нужный main.cpp и нажимайте F5. Каждый урок имеет локальные задачи
Windows/Linux и использует общие скрипты из корня репозитория. Обычные уроки
выбирают системный GCC, современные — CXX_MODERN; версии и зависимости
обозначены отдельно. Сборка всех примеров и проверка результатов:

```bash
python3 scripts/check-bonuses.py --section basics/bonus
```

На Windows вместо python3 можно использовать python; запускайте из корня.
Проверки создают временные данные только в build/ и не меняют учебные файлы.
Linux ещё предстоит проверить на Ubuntu. [Статус проверки Windows и её ограничения](../../bonus/reflection/VALIDATION.md)
сохранены отдельно; воспроизводимый сценарий находится в репозитории.

## Дополнительно

В уроке 24 открывайте src/main.cpp: он собирается вместе с support.cpp.
Отрицательные примеры не выполняются обычным F5. ASan-проверка урока 29
выделена в run-sanitizers.sh и требует Linux/WSL с установленной поддержкой.
Все основные примеры используют ASCII-вывод без перенастройки консоли.
Контейнеры, optional/variant, string_view/span и ranges подробно изучаются
в разделе STL; здесь библиотечные типы служат иллюстрациями механизмов языка.
