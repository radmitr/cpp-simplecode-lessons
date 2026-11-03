# Курсы и справочники

## Исходный курс

Автор уроков, на которых основан проект, — **Сергей Журавлёв (#SimpleCode)**:
[канал YouTube](https://www.youtube.com/@SimpleCodeIT),
[профиль Udemy](https://www.udemy.com/user/zhuravliov-sergei/).
Этот репозиторий — личная переработка и справочник с самостоятельными дополнениями.

Проверенные ссылки на начала тематических плейлистов:

- [Основы C++, урок 0: установка Visual Studio](https://www.youtube.com/watch?v=kRcbYLK3OnQ&list=PLQOaTSbfxUtCrKs0nicOg2npJQYSPGO9r).
  Для этой рабочей папки используйте [настройку GCC и VS Code](../README.md#требования).
- [ООП, урок 72: введение](https://www.youtube.com/watch?v=rZcTaRU7AAw&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX).
- [STL, урок 1: vector](https://www.youtube.com/watch?v=1cKvMZOJeeE&list=PLQOaTSbfxUtDWAtIYme5MLZ1l0GTyUYkB).
- [Динамические структуры данных, односвязный список, часть 1](https://www.youtube.com/watch?v=C9FK1pHLnhI&list=PLQOaTSbfxUtAIipl4136nwb4ISyFk8oI4).
  Соответствует теме местных уроков [«133. Односвязный список: узлы и доступ»](../basics/lesson-133-singly-linked-list-part1/README.md) — [«135. Односвязный список: полный интерфейс»](../basics/lesson-135-singly-linked-list-part3/README.md).
- [Многопоточность, урок 1: thread](https://www.youtube.com/watch?v=NawpxG81RRk&list=PLQOaTSbfxUtAc_RpyDiWCHq0YTzLtVSD0).

Видеоурок и текущий исходник могут различаться переносимостью, исправлениями
и способом сборки. Страница [«Курс и учебные примеры»](course-sources.md)
описывает устройство справочника и проверку программ.

## Точный контракт языка и библиотеки

[`eel.is/c++draft`](https://eel.is/c++draft/) — HTML-представление
**рабочего проекта стандарта C++**, подготовленное из исходников проекта.
Это не официальный опубликованный ISO-документ и не вводный учебник.
В нём удобно искать точные требования: что допускает функция, что она
возвращает, когда блокируется и какие ошибки предусмотрены.
Текст относится к развивающемуся проекту; новая формулировка не означает,
что ваш компилятор уже поддерживает её.

Полезные разделы: [потоки](https://eel.is/c++draft/thread),
[контейнеры](https://eel.is/c++draft/containers),
[диагностика и исключения](https://eel.is/c++draft/diagnostics).
Для даты появления API сопоставляйте текст с
[версией C++ и поддержкой библиотеки](cpp-versions.md).

[Открытые материалы комитета WG21](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/)
содержат предложения и проекты. Предложение само по себе ещё не является
принятым стандартом. [Обзор стандартов ISO C++](https://isocpp.org/std/the-standard)
объясняет статус публикаций.

## Практическая справка

- [cppreference](https://en.cppreference.com/w/cpp) — независимая справка:
  сигнатуры, заголовки, метки `since C++11/20`, примеры и ограничения.
  Удобна для поиска API, но не является самим стандартом.
- [Microsoft Learn: стандартная библиотека C++](https://learn.microsoft.com/en-us/cpp/standard-library/cpp-standard-library-reference?view=msvc-170)
  — документация поставщика; особенности MSVC проверяйте отдельно от MinGW/GCC.
- [GCC: статус стандартной библиотеки](https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html)
  — поддержка API в libstdc++ по версиям языка.
- [GCC: диалект C++ и флаги](https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html)
  — что выбирает `-std=...` и какие расширения доступны.
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
  — рекомендации по проектированию, владению и обработке ошибок.
  Рекомендация и обязательное правило языка — разные вещи.
- [VS Code: сочетания клавиш отладки](https://code.visualstudio.com/docs/reference/default-keybindings#_debug)
  — стандартные действия F5 и Ctrl+F5; свои клавиши можно переназначить.

Сначала читайте объяснение и запускайте локальный пример. Внешняя ссылка
нужна для проверки точной формулировки и дальнейшего чтения;
она не заменяет разбор программы в README урока.
