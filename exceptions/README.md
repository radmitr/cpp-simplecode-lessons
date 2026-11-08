# Исключения и обработка ошибок

Исключение передаёт управление от места ошибки к подходящему обработчику.
Сначала изучите функции, области видимости, классы и деструкторы.
[RAII](../basics/additions/09-raii/README.md) объясняет, как освобождать ресурсы
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

После курса: [типы исключений](additions/01-exception-types/README.md) →
[повторное выбрасывание и вложенные причины](additions/02-rethrow-and-nested/README.md) →
[noexcept](additions/03-noexcept/README.md) →
[гарантии безопасности](additions/04-exception-guarantees/README.md).

Дополнительно: [ошибки через future/promise](../multithreading/additions/11-promise-future/README.md)
и [результат или ошибка: expected](../stl/additions/07-expected/README.md).
`expected` не создаёт поток; `future` не является общей заменой `join()`.
[Все дополнения исключений](additions/README.md).

## Сборка и запуск

[Запуск в VS Code](../README.md#сборка-и-запуск-в-vs-code) ·
[Команды терминала](../README.md#сборка-из-терминала).
Дополнения собираются как C++17; сами исключения языка — C++98,
`noexcept` и вложенные исключения — C++11.

Из корня: `python scripts/check-additions.py --section exceptions/additions`
(Linux: `python3`). Эта команда не запускает аварийные примеры курса.
[Версии C++](../docs/cpp-versions.md) · [Каталог](../LESSONS.md).
