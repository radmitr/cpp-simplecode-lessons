# Бонусы по шаблонам

Дополнения к [урокам курса](../README.md). Прежние номера бонусов сохранены,
поэтому список начинается с 16. Исходным бонусам нужен C++17, concepts — C++20; новые дополнения используют C++23/26.

1. [16. Шаблоны функций и вывод параметров](16-function-templates/README.md).
2. [17. Параметры шаблонов, специализация и CTAD](17-template-parameters/README.md).
3. [18. type_traits, `if constexpr` и enable_if](18-traits-if-constexpr/README.md).
4. [19. Пакеты параметров и fold expressions](19-parameter-packs/README.md).
5. [20. Forwarding references и std::forward](20-perfect-forwarding/README.md).
6. [21. Concepts и requires](21-concepts/README.md).

Сначала нужны функции, ссылки, классы и шаблоны курса. Перемещение разобрано
в [бонусе основ](../../basics/bonus/09-move-semantics/README.md).
Для более сложного исследования типов есть
[рефлексия](../../bonus/reflection/README.md).

[Общий запуск Windows/Linux](../../README.md#сборка-и-запуск-в-vs-code).
Ввод, результат и ограничения каждого варианта описаны в его README.
Проверка из корня: `python scripts/check-bonuses.py --section templates/bonus`
(Linux: `python3`). [Каталог уроков](../../LESSONS.md).

## Дополнения современных стандартов

- [Индексирование пакета параметров](22-pack-indexing/README.md) — `c++26`.
- [Перенос квалификаторов через forward_like](23-forward-like/README.md) — `c++23`.

[Порядок изучения и карта тем](../../docs/modern-cpp.md). Требования и команды находятся в README каждого урока.
