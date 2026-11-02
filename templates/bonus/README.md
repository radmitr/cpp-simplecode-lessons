# Бонусы по шаблонам

Дополнения к [урокам курса](../README.md). Прежние номера бонусов сохранены,
поэтому список начинается с 16. В основном нужен C++17; последний урок — C++20.

1. [16. Шаблоны функций и вывод параметров](16-function-templates/README.md).
2. [17. Параметры, специализация и CTAD](17-template-parameters/README.md).
3. [18. Свойства типов, if constexpr и enable_if](18-traits-if-constexpr/README.md).
4. [19. Пакеты параметров и свёртки](19-parameter-packs/README.md).
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
