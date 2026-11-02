# Исключения и обработка ошибок

Исключение передаёт управление от места ошибки к подходящему обработчику.
Сначала изучите функции, области видимости, классы и деструкторы.
[RAII](../basics/bonus/02-raii/README.md) объясняет, как освобождать ресурсы
при обычном выходе и при передаче исключения.

## Уроки курса

1. [120. Обработка исключений: try и catch](lesson-120-exception-handling-try-catch/README.md).
2. [121. Выбрасывание исключений: throw](lesson-121-exception-throw/README.md).
3. [122. Несколько обработчиков catch](lesson-122-multiple-catch-blocks/README.md).
4. [123. Собственные классы исключений](lesson-123-custom-exception-class/README.md).

Номера, имена папок и варианты исходного курса сохранены.
В некоторых примерах ожидается неперехваченное исключение или требуется файл:
перед запуском читайте README конкретного урока.

## Дополнения и порядок

После курса: [типы исключений](bonus/30-exception-types/README.md) →
[повторное выбрасывание и вложенные причины](bonus/13-rethrow-and-nested/README.md) →
[noexcept](bonus/14-noexcept/README.md) →
[гарантии безопасности](bonus/15-exception-guarantees/README.md).

Дополнительно: [ошибки через future/promise](../multithreading/bonus/09-promise-future/README.md)
и [результат или ошибка: expected](../stl/bonus/04-expected/README.md).
`expected` не создаёт поток; `future` не является общей заменой `join()`.
[Все бонусы исключений](bonus/README.md).

## Сборка и запуск

[Запуск в VS Code](../README.md#сборка-и-запуск-в-vs-code) ·
[Команды терминала](../README.md#сборка-из-терминала).
Бонусы собираются как C++17; сами исключения языка — C++98,
`noexcept` и вложенные исключения — C++11.

Из корня: `python scripts/check-bonuses.py --section exceptions/bonus`
(Linux: `python3`). Эта команда не запускает аварийные примеры курса.
[Версии C++](../docs/cpp-versions.md) · [Каталог](../LESSONS.md).
