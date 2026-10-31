# Рефлексия и исследование типов в C++

Самостоятельное направление из 30 уроков.
Уроки 01–05 работают на C++17 и показывают возможности до стандартной рефлексии.
Уроки 06–30 используют C++26, GCC 16+ и -freflection. Сначала изучите шаблоны,
[constexpr/consteval](../../basics/bonus/01-constexpr-consteval/README.md)
и [RAII](../../basics/bonus/02-raii/README.md). Номера — последовательность обучения,
а прикладные уроки используют небольшие общие функции из common/reflection.hpp.

## Уроки

1. [Интроспекция, метаданные и время выполнения](01-introspection-overview/README.md) — c++17.
2. [RTTI: typeid, type_info и type_index](02-typeid-type-index/README.md) — c++17.
3. [Проверяемые преобразования dynamic_cast](03-dynamic-cast/README.md) — c++17.
4. [decltype, type_traits и обнаружение операций](04-traits-and-detection/README.md) — c++17.
5. [Ручные описатели и указатели на члены](05-manual-descriptors/README.md) — c++17.
6. [Компилятор, заголовок meta и проверка возможностей](06-toolchain/README.md) — c++26, GCC 16+.
7. [Оператор ^^ и std::meta::info](07-reflection-info/README.md) — c++26, GCC 16+.
8. [Имена, псевдонимы, родитель и исходник](08-names-and-origins/README.md) — c++26, GCC 16+.
9. [Splicing: переход от метаданных к программе](09-splicing/README.md) — c++26, GCC 16+.
10. [Перечисления и совпадающие значения](10-enumerators/README.md) — c++26, GCC 16+.
11. [Поля, типы и фильтрация членов](11-data-members/README.md) — c++26, GCC 16+.
12. [Контекст доступа и инкапсуляция](12-access-control/README.md) — c++26, GCC 16+.
13. [Развёртывание обхода и runtime-значения](13-expansion-statements/README.md) — c++26, GCC 16+.
14. [Базовые классы и подобъекты](14-base-subobjects/README.md) — c++26, GCC 16+.
15. [Функции, параметры и вызовы](15-functions-and-parameters/README.md) — c++26, GCC 16+.
16. [Отражение шаблонов и подстановка](16-templates/README.md) — c++26, GCC 16+.
17. [Размеры, выравнивание и смещения](17-layout/README.md) — c++26, GCC 16+.
18. [Пользовательские аннотации](18-annotations/README.md) — c++26, GCC 16+.
19. [Статическое хранение вычисленных данных](19-static-storage/README.md) — c++26, GCC 16+.
20. [Создание агрегатного типа](20-define-aggregate/README.md) — c++26, GCC 16+.
21. [Защитные запросы и ошибки метафункций](21-diagnostics/README.md) — c++26, GCC 16+.
22. [Заголовки и несколько единиц трансляции](22-odr-and-headers/README.md) — c++26, GCC 16+.
23. [Практика: enum в строку и обратно](23-enum-conversion/README.md) — c++26, GCC 16+.
24. [Практика: вывод вложенных структур](24-recursive-print/README.md) — c++26, GCC 16+.
25. [Практика: сравнение, копирование и хеширование](25-memberwise-operations/README.md) — c++26, GCC 16+.
26. [Практика: структура и tuple ссылок](26-struct-to-tuple/README.md) — c++26, GCC 16+.
27. [Практика: имена полей и проверка конфигурации](27-cli-configuration/README.md) — c++26, GCC 16+.
28. [Практика: JSON без ручного списка полей](28-json-serialization/README.md) — c++26, GCC 16+.
29. [Итог: загрузка, проверка и сохранение настроек](29-settings-project/README.md) — c++26, GCC 16+.
30. [Границы, переносимость и стоимость](30-limits-and-cost/README.md) — c++26, GCC 16+.

## Как работать

Открывайте нужный main.cpp и нажимайте F5. Каждый урок имеет локальные задачи
Windows/Linux и использует общие скрипты из корня репозитория. Обычные уроки
выбирают системный GCC, современные — CXX_MODERN; версии и зависимости
обозначены отдельно. Сборка всех примеров и проверка результатов:

```bash
python3 scripts/check-bonuses.py --section bonus/reflection
```

На Windows вместо python3 можно использовать python; запускайте из корня.
Проверки создают временные данные только в build/ и не меняют учебные файлы.
Linux ещё предстоит проверить на Ubuntu. [Статус проверки Windows и её ограничения](VALIDATION.md)
сохранены отдельно; воспроизводимый сценарий находится в репозитории.

## Подготовка и справочники

- [Windows и зависимости](dependencies.md).
- [Ubuntu 22.04: сборка GCC в /home и установка в /opt/gcc-16](linux-setup.md).
- [Карта API и ограничения](API.md).
- [Отрицательные примеры и проверка](checks/README.md).

Уроки 01–05 можно изучать на системном GCC 11 независимо от установки нового GCC.
Остальные уроки Linux должны быть отдельно проверены после установки: настройки
подготовлены, но успешный запуск Windows не считается проверкой Ubuntu.
