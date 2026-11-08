# Современные дополнения C++20–26

Это тематический указатель современных дополнений, а не заявление о покрытии всего C++.
Для всех редакций есть [указатель версий](cpp-versions.md),
[учебный маршрут](learning-path.md) и [карта покрытия](cpp-coverage.md).
Каждый урок содержит исходники, проверки результатов, требования и отдельные
конфигурации запуска Linux/Windows. Варианты `main.cpp`, `main2.cpp` и далее
запускаются независимо. Примеры курса SimpleCode сохраняют исходные папки и номера.

## Связи тем

1. После функций, ссылок и RAII изучите явный параметр объекта, `if consteval`,
   новые операторы и утилиты перечислений/байтов.
2. Начните диапазоны с представлений C++20, затем переходите к адаптерам C++23.
3. После умных указателей изучите вызываемые обёртки и семантику владения.
4. После многомерных массивов изучите `mdspan`, затем линейную алгебру.
5. После RAII и исключений изучите собственную корутину, затем `std::generator`.
6. После потоков и корутин переходите к senders/receivers и планировщику.
   Контракты изучаются независимо после функций и проверки входных данных.

## Карта уроков

| Тема | Версия | Требования |
|---|---|---|
| [if consteval и явное копирование auto](../basics/additions/20-consteval-and-auto-copy/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Перечисления и порядок байтов](../basics/additions/25-enums-and-bytes/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Предположения оптимизатору и недостижимый код](../basics/additions/33-assume-and-unreachable/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Вычисляемые сообщения и удалённые функции](../basics/additions/34-compile-time-diagnostics/README.md) | C++26 | Учебная конфигурация GCC 16+ |
| [Пакеты структурированных привязок](../basics/additions/35-structured-bindings-packs/README.md) | C++26 | Учебная конфигурация GCC 16+ |
| [Предусловия, постусловия и проверки контракта](../additions/contracts/01-contract-checks/README.md) | C++26 | Учебная конфигурация GCC 16+ |
| [Корутина, приостановка и владение кадром](../additions/coroutines/01-coroutine-lifetime/README.md) | C++20 | Учебная конфигурация GCC 16+ |
| [Стандартный генератор последовательности](../additions/coroutines/02-standard-generator/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Описание работы через senders и receivers](../additions/execution/01-senders/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [Планировщик и время жизни операции](../additions/execution/05-schedulers/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [Потоки над готовым буфером](../io/additions/08-spanstream/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Включение файла через embed](../io/additions/25-embed/README.md) | C++26 | Учебная конфигурация GCC 16+ |
| [Получение стека вызовов](../io/additions/23-stacktrace/README.md) | C++23 | Feature-test macro; возможен `UNAVAILABLE` |
| [Взаимодействие с отладчиком](../io/additions/24-debugging/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [Явный параметр объекта](../oop/additions/03-explicit-object/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Многомерный индекс и статические операторы](../oop/additions/04-call-and-subscript/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Диапазоны, представления и время жизни](../stl/additions/11-ranges-and-views/README.md) | C++20 | Учебная конфигурация GCC 16+ |
| [Адаптеры и алгоритмы диапазонов](../stl/additions/12-ranges-adaptors/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [flat_map и flat_set](../stl/additions/15-flat-containers/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Многомерное представление mdspan](../stl/additions/22-mdspan/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Вызываемые объекты без копирования](../stl/additions/17-move-only-function/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Вектор с фиксированной вместимостью](../stl/additions/16-inplace-vector/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [Блочный контейнер hive](../stl/additions/25-hive/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [Владение с копированием значения](../stl/additions/19-value-wrappers/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [Ссылка на функцию и копируемая обёртка](../stl/additions/18-function-wrappers/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [optional со ссылкой и обход optional](../stl/additions/10-optional-reference/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [Поиск подстроки и заполнение строки](../stl/additions/13-string-operations/README.md) | C++23 | Учебная конфигурация GCC 16+ |
| [Поэлементные вычисления SIMD](../stl/additions/23-simd/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [Линейная алгебра поверх mdspan](../stl/additions/24-linalg/README.md) | C++26 | Feature-test macro; возможен `UNAVAILABLE` |
| [Индексирование пакета параметров](../templates/additions/08-pack-indexing/README.md) | C++26 | Учебная конфигурация GCC 16+ |
| [Перенос квалификаторов через forward_like](../templates/additions/07-forward-like/README.md) | C++23 | Учебная конфигурация GCC 16+ |

| [Режимы проверки и обработчик нарушения](../additions/contracts/02-evaluation-modes/README.md) | C++26 | GCC 16+; `-fcontracts` |
| [Порядок проверок и выход по исключению](../additions/contracts/03-order-and-exceptions/README.md) | C++26 | GCC 16+; `-fcontracts` |
| [Инварианты класса и внешний ввод](../additions/contracts/04-invariants-and-input/README.md) | C++26 | GCC 16+; `-fcontracts` |
| [Протокол co_await и собственный awaiter](../additions/coroutines/03-await-protocol/README.md) | C++20 | GCC 16+ |
| [Результат задачи и распространение исключений](../additions/coroutines/04-task-result/README.md) | C++20 | GCC 16+ |
| [Время жизни параметров и захватов корутины](../additions/coroutines/05-parameters-and-captures/README.md) | C++20 | GCC 16+ |
| [Кооперативная отмена корутины](../additions/coroutines/06-cooperative-cancellation/README.md) | C++20 | GCC 16+ |
| [Безопасная передача возобновления другому потоку](../additions/coroutines/07-thread-handoff/README.md) | C++20 | GCC 16+ |
| [Несколько модулей, повторный экспорт и шаблоны](../additions/modules/02-reexport-and-templates/README.md) | C++20 | GCC 16+; module helper |
| [Разделы модуля и global module fragment](../additions/modules/03-partitions-and-global-fragment/README.md) | C++20 | GCC 16+; module helper |
| [Header units и макросы](../additions/modules/04-header-units/README.md) | C++20 | GCC 16+; module helper |
| [Стандартный модуль и пересоздание CMI](../additions/modules/05-import-std/README.md) | C++23 | GCC 16+; module helper |
| [connect, start и собственный receiver](../additions/execution/02-operation-state/README.md) | C++26 | Стандартный API или явный stdexec |
| [Значение, ошибка и остановка](../additions/execution/03-completion-channels/README.md) | C++26 | Стандартный API или явный stdexec |
| [Объединение операций и зависимые шаги](../additions/execution/04-composition/README.md) | C++26 | Стандартный API или явный stdexec |
| [Переключение планировщика](../additions/execution/06-scheduler-transfer/README.md) | C++26 | Стандартный API или явный stdexec |
| [Senders внутри корутины](../additions/execution/07-coroutine-interop/README.md) | C++26 | Стандартный API или явный stdexec |

Также расширены существующие уроки:

- [Результат или ошибка](../stl/additions/07-expected/README.md): цепочки `expected`,
  обработка ошибки, `expected<void,E>` и сравнение с цепочками `optional`.
- [Форматирование и печать](../io/additions/05-format-and-print/README.md): диапазоны,
  tuple, прямые вызовы `print`/`println` и formatter пользовательского типа.
- [Рефлексия](../additions/reflection/README.md) уже демонстрирует `^^`, splicing,
  `template for`, аннотации, создание агрегатов и обработку ошибки метафункции
  при константном вычислении. Эти примеры не дублируются.

## Поддержка и запуск

[Настройка GCC](../additions/reflection/linux-setup.md) и
[сборка и запуск в VS Code](../README.md#сборка-и-запуск-в-vs-code).
После добавления исходников выполните `C/C++: Update IntelliSense`.
Сборка нового урока требует GCC 16+ через `CXX_MODERN`, даже если отдельная
возможность появилась в более раннем GCC. Это единая учебная конфигурация,
а не утверждение о минимальной версии реализации каждой функции.

Обычный C++26 не требует `-freflection`. Этот флаг нужен существующим урокам
рефлексии; для контрактов отдельно используется `-fcontracts`.
IntelliSense может отставать от GCC и ошибочно подчёркивать новые конструкции:
сообщение редактора и результат реальной сборки нужно различать.

В установленной учебной libstdc++ 16.2.0 отсутствуют `<hive>`, `<linalg>` и
senders/receivers из C++26. Их исходники содержат стандартные вызовы под
условием feature-test macro; при отсутствии поддержки программа возвращает
`77` с сообщением `UNAVAILABLE`. Такая ветка не подтверждает работоспособность
основного примера. Для практического изучения добавлен явный
[внешний профиль](../additions/execution/reference-libraries.md) с закреплёнными
stdexec, stdBLAS/mdspan и plf::hive. Его успешные результаты относятся к этим
реализациям; стандартный профиль по-прежнему отдельно сообщает об отсутствии API.
Наличие `<execution>` с политиками C++17 не включает senders C++26.

Интерфейсы экспериментальных реализаций меняются. Например, текущий `<simd>`
использует `std::simd::vec`, а новая редакция `inplace_vector::try_push_back`
возвращает `optional<T&>` вместо указателя. Сверяйте feature-test macros и
контракт своей версии библиотеки; один `-std=c++26` не гарантирует всё API.

Проверка существующих и новых дополнений из корня:

```bash
python3 scripts/check-additions.py --section all
```

`SKIP` для отсутствующей возможности показывается отдельно и не считается
успешным запуском. Чтобы потребовать все реализации, добавьте
`--require-features`; тогда отсутствие стандартного API считается ошибкой.
Проверки оставляют файлы и отчёт только в `build/`.

## Границы справочника

README описывают основные варианты API, порядок действий, владение, время жизни,
ошибки и существенные ограничения на примерах. Они не заменяют стандарт и
не перечисляют все возможные пользовательские типы, специализации или комбинации
параметров. Намеренно неверные операции помечены; неопределённое поведение не
запускается. Внешние первичные источники уточняют точные требования.

- [Появление возможностей и режим сборки](cpp-versions.md).
- [Статус языка GCC](https://gcc.gnu.org/projects/cxx-status.html).
- [Статус libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html).
- [Рабочий проект стандарта](https://eel.is/c++draft/): технический справочник,
  а не учебник и не опубликованный документ ISO.
