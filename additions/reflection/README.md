# Рефлексия и исследование типов в C++

Самостоятельное направление из 30 уроков.
Уроки [«01. Интроспекция, метаданные и время выполнения»](01-introspection-overview/README.md) — [«05. Ручные описатели и указатели на члены»](05-manual-descriptors/README.md) работают на C++17 и показывают возможности до стандартной рефлексии.
Уроки от [проверки компилятора](06-toolchain/README.md) до
[границ и стоимости рефлексии](30-limits-and-cost/README.md) используют C++26,
GCC 16+ и `-freflection`. Сначала изучите шаблоны,
[constexpr/consteval](../../basics/additions/19-constexpr-consteval/README.md)
и [RAII](../../basics/additions/09-raii/README.md). Номера — последовательность обучения,
а прикладные уроки используют небольшие общие функции из `common/reflection.hpp`.

## Уроки

- [01. Интроспекция, метаданные и время выполнения](01-introspection-overview/README.md) — `c++17`.
- [02. RTTI: `typeid`, `type_info` и `type_index`](02-typeid-type-index/README.md) — `c++17`.
- [03. Проверяемые преобразования `dynamic_cast`](03-dynamic-cast/README.md) — `c++17`.
- [04. `decltype`, `type_traits` и обнаружение операций](04-traits-and-detection/README.md) — `c++17`.
- [05. Ручные описатели и указатели на члены](05-manual-descriptors/README.md) — `c++17`.
- [06. Компилятор, заголовок meta и проверка возможностей](06-toolchain/README.md) — `c++26`.
- [07. Оператор `^^` и `std::meta::info`](07-reflection-info/README.md) — `c++26`.
- [08. Имена, псевдонимы, родитель и исходник](08-names-and-origins/README.md) — `c++26`.
- [09. Статическое хранение вычисленных данных](09-static-storage/README.md) — `c++26`.
- [10. Splicing: переход от метаданных к программе](10-splicing/README.md) — `c++26`.
- [11. Контекст доступа и инкапсуляция](11-access-control/README.md) — `c++26`.
- [12. Поля, типы и фильтрация членов](12-data-members/README.md) — `c++26`.
- [13. Развёртывание обхода и runtime-значения](13-expansion-statements/README.md) — `c++26`.
- [14. Перечисления и совпадающие значения](14-enumerators/README.md) — `c++26`.
- [15. Практика: `enum` в строку и обратно](15-enum-conversion/README.md) — `c++26`.
- [16. Базовые классы и подобъекты](16-base-subobjects/README.md) — `c++26`.
- [17. Функции, параметры и вызовы](17-functions-and-parameters/README.md) — `c++26`.
- [18. Отражение шаблонов и подстановка](18-templates/README.md) — `c++26`.
- [19. Размеры, выравнивание и смещения](19-layout/README.md) — `c++26`.
- [20. Пользовательские аннотации](20-annotations/README.md) — `c++26`.
- [21. Создание агрегатного типа](21-define-aggregate/README.md) — `c++26`.
- [22. Защитные запросы и ошибки метафункций](22-diagnostics/README.md) — `c++26`.
- [23. Заголовки и несколько единиц трансляции](23-odr-and-headers/README.md) — `c++26`.
- [24. Практика: вывод вложенных структур](24-recursive-print/README.md) — `c++26`.
- [25. Практика: сравнение, копирование и хеширование](25-memberwise-operations/README.md) — `c++26`.
- [26. Практика: структура и `tuple` ссылок](26-struct-to-tuple/README.md) — `c++26`.
- [27. Практика: имена полей и проверка конфигурации](27-cli-configuration/README.md) — `c++26`.
- [28. Практика: JSON без ручного списка полей](28-json-serialization/README.md) — `c++26`.
- [29. Итог: загрузка, проверка и сохранение настроек](29-settings-project/README.md) — `c++26`.
- [30. Границы, переносимость и стоимость](30-limits-and-cost/README.md) — `c++26`.

## Как работать

Открывайте нужный `main.cpp` и нажимайте F5/Ctrl+F5. Каждый урок имеет локальные задачи
Windows/Linux и использует общие скрипты из корня репозитория. Обычные уроки
выбирают системный GCC, современные — `CXX_MODERN`; версии и зависимости
обозначены отдельно. Сборка всех примеров и проверка результатов:

```bash
python3 scripts/check-additions.py --section additions/reflection
```

На Windows вместо python3 можно использовать python; запускайте из корня.
Проверки создают временные данные только в `build/` и не меняют учебные файлы.

## Подготовка и справочники

- [Windows и зависимости](dependencies.md).
- [Ubuntu 22.04: сборка GCC в /home и установка в /opt/gcc/16](linux-setup.md).
- [Карта API и ограничения](API.md).
- [Отрицательные примеры и проверка](checks/README.md).

Уроки [«01. Интроспекция, метаданные и время выполнения»](01-introspection-overview/README.md) — [«05. Ручные описатели и указатели на члены»](05-manual-descriptors/README.md) можно изучать на системном GCC 11 независимо от установки нового GCC.
