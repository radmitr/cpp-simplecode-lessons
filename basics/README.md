# Основы C++

Уроки курса с сохранёнными номерами. [Правила разделения курса и дополнений](../docs/course-sources.md)
помогают ориентироваться в примерах; особенности реализации описаны в уроках.
Пропуски номеров не заполняются выдуманными темами.
Пояснения к вариантам `main*.cpp`, ожидаемому поведению и ограничениям находятся
в README каждого урока. Новые темы размещаются в [additions](additions/README.md).

## Как изучать

Для начала с нуля проходите уроки [«001. Первая программа»](lesson-001-hello-world/README.md) — [«028. Размер объекта: sizeof»](lesson-028-sizeof/README.md), затем массивы, функции и память
031–070. После них — [введение в ООП, уроки 073–081](../oop/README.md).
Для шаблонов классов и владения памятью полезны [уроки ООП](../LESSONS.md#ооп).
Тематический порядок ниже дополняет исходную нумерацию курса.

- Массивы 58–59 изучайте после указателей; обработка ошибки в 59 использует исключения 120–123.
- Указатели на функции 65 → `std::function` 142 → лямбды 143–144 → функторы 146 → предикаты 147.
- [Файлы и потоки 115–119](../io/README.md) → исключения 120–123.
- Шаблоны 126–128 → умные указатели 130–132 → список 133–135.
- [constexpr/consteval](additions/19-constexpr-consteval/README.md) — после функций; перед изучением статической рефлексии.
- [RAII](additions/09-raii/README.md) — после деструкторов и `try`/`catch`; связывает файлы, память и исключения.

## Начальные уроки курса

- [001. Первая программа](lesson-001-hello-world/README.md).
- [002. Устройство программы](lesson-002-program-structure/README.md).
- [003. Управляющие последовательности](lesson-003-escape-sequences/README.md).
- [004. Основные типы данных](lesson-004-data-types/README.md).
- [005. Переменные и присваивание](lesson-005-variables/README.md).
- [006. Константы](lesson-006-const/README.md).
- [007. Ввод через std::cin](lesson-007-cin/README.md).
- [008. Арифметические операторы](lesson-008-arithmetic-operators/README.md).
- [009. Префиксные и постфиксные ++ и --](lesson-009-increment-decrement/README.md).
- [010. Составное присваивание](lesson-010-compound-assignment/README.md).
- [011. Сравнения и логические операции](lesson-011-logical-operators/README.md).
- [012. Ветвление if и else](lesson-012-if-else/README.md).
- [013. Выбор switch](lesson-013-switch/README.md).
- [014. Цикл while](lesson-014-while/README.md).
- [015. Цикл do-while](lesson-015-do-while/README.md).
- [016. Цикл for](lesson-016-for/README.md).
- [017. Варианты записи for](lesson-017-for-variants/README.md).
- [018. Выход из цикла: break](lesson-018-break/README.md).
- [019. Переход к следующей итерации: continue](lesson-019-continue/README.md).
- [020. Исходник и исполняемый файл](lesson-020-executable/README.md).
- [021. Почему закрывается консоль](lesson-021-console-pause/README.md).
- [022. Переход goto](lesson-022-goto/README.md).
- [023. Пошаговая отладка](lesson-023-debugging/README.md).
- [024. Вложенные циклы](lesson-024-nested-loops/README.md).
- [025. Одномерный массив](lesson-025-array/README.md).
- [026. Инициализация массива](lesson-026-array-initialization/README.md).
- [027. Заполнение и вывод массива циклом](lesson-027-array-loops/README.md).
- [028. Размер объекта: sizeof](lesson-028-sizeof/README.md).
- [031. Инициализация двумерного массива](lesson-031-2d-array-initialization/README.md).
- [032. Заполнение и вывод двумерного массива](lesson-032-2d-array-loops/README.md).
- [033. Функции и возвращаемое значение](lesson-033-functions/README.md).
- [034. Передача аргументов по значению](lesson-034-function-value-parameters/README.md).
- [035. Массив как параметр функции](lesson-035-array-function-parameters/README.md).
- [036. Предварительное объявление функции](lesson-036-function-prototypes/README.md).
- [037. Глобальные и локальные переменные](lesson-037-variable-scope/README.md).
- [038. Аргументы по умолчанию](lesson-038-default-arguments/README.md).
- [039. Функции inline](lesson-039-inline-functions/README.md).
- [040. Перегрузка функций](lesson-040-function-overloading/README.md).
- [042. Вызовы функций и стек](lesson-042-call-stack/README.md).
- [043. Рекурсивный вызов](lesson-043-recursion/README.md).
- [044. Рекурсивный факториал](lesson-044-recursive-factorial/README.md).
- [046. Указатели и разыменование](lesson-046-pointers/README.md).
- [047. Арифметика указателей](lesson-047-pointer-arithmetic/README.md).
- [048. Параметр-указатель](lesson-048-pointer-parameters/README.md).
- [049. Несколько результатов через указатели](lesson-049-multiple-results-pointers/README.md).
- [050. Ссылки на объекты](lesson-050-references/README.md).
- [051. Передача по значению, ссылке и указателю](lesson-051-reference-parameters/README.md).
- [052. Несколько результатов через ссылки](lesson-052-multiple-results-references/README.md).
- [053. Динамическая память: new и delete](lesson-053-new-delete/README.md).
- [054. Нулевой указатель](lesson-054-nullptr/README.md).
- [055. Одномерный динамический массив](lesson-055-dynamic-array/README.md).
- [056. Двумерный динамический массив](lesson-056-2d-dynamic-array/README.md).
- [057. const в параметрах и указателях](lesson-057-const-pointer-parameters/README.md).
- [060. Символьные строки и нулевой терминатор](lesson-060-c-strings/README.md).
- [061. Неявное и явное преобразование типов](lesson-061-type-conversions/README.md).
- [063. Строки, указатели и функции](lesson-063-c-string-functions/README.md).
- [066. Препроцессор и define](lesson-066-define/README.md).
- [067. Макросы с параметрами](lesson-067-function-like-macros/README.md).
- [068. Условная компиляция](lesson-068-conditional-compilation/README.md).
- [069. Условный оператор ?:](lesson-069-conditional-operator/README.md).
- [070. Аргументы командной строки](lesson-070-argc-argv/README.md).

## Числа, строки и массивы

- [29. Псевдослучайные числа: rand и srand](lesson-029-rand/README.md).
- [58. Копирование динамического массива](lesson-058-dynamic-array-copy/README.md).
- [59. Изменение динамического массива](lesson-059-dynamic-array-resize-delete-add-get/README.md).
- [62. Коды символов и ASCII](lesson-062-ascii/README.md).
- [64. Конкатенация строк](lesson-064-string-concat/README.md).

## Вызываемые объекты

- [65. Указатели на функции](lesson-065-function-pointers/README.md).
- [142. Хранение вызываемых объектов: std::function](lesson-142-std-functional/README.md).
- [143. Лямбда-выражения](lesson-143-lambda/README.md).
- [144. Захваты и возвращаемый тип лямбды](lesson-144-lambda-capture-context/README.md).
- [146. Функторы: operator()](lesson-146-functors/README.md).
- [147. Предикаты](lesson-147-predicates/README.md).

## Исключения

Выделены в [отдельный раздел](../exceptions/README.md): уроки курса и дополнения.

## Типы и объявления

- [124. Перечисления enum](lesson-124-enum-types/README.md).
- [125. Пространства имён](lesson-125-namespaces/README.md).
- [129. struct и class](lesson-129-structures-struct-vs-class/README.md).
- [136. Вывод типа через auto](lesson-136-auto-keyword/README.md).
- [137. Цикл по диапазону](lesson-137-range-based-for-loop/README.md).
- [138. Псевдонимы типов: typedef](lesson-138-typedef-keyword/README.md).
- [141. Объединения union](lesson-141-union/README.md).

## Шаблоны

[Шаблоны функций и классов](../templates/README.md) и их дополнения теперь собраны отдельно.

## Владение памятью и структуры данных

- [130. Учебный умный указатель](lesson-130-smart-pointers/README.md).
- [131. Виды умных указателей](lesson-131-smart-pointers-types/README.md).
- [132. Умные указатели на динамические массивы](lesson-132-smart-pointers-dynamic-arrays/README.md).
- [133. Односвязный список: узлы и доступ](lesson-133-singly-linked-list-part1/README.md).
- [134. Односвязный список: удаление](lesson-134-singly-linked-list-part2/README.md).
- [135. Односвязный список: полный интерфейс](lesson-135-singly-linked-list-part3/README.md).

## Организация программы и измерения

- [139. Многофайловая программа](lesson-139-multi-file-project/README.md).
- [140. Защита заголовков от повторного включения](lesson-140-multi-file-project-include-guard/README.md).
- [145. Измерение времени выполнения](lesson-145-measure-execution-time/README.md).

## Сборка и запуск

Основные уроки используют C++17. Дополнение `constexpr`/`consteval` выбирает C++20
через `cxx-standard.txt`. На Ubuntu 22.04 для этих дополнений подходит GCC 11;
GCC 16 и C++26 нужны для [самостоятельного раздела рефлексии](../additions/reflection/README.md).

В VS Code откройте исходник с `main()`: Ctrl+Shift+B собирает, F5 запускает с отладчиком, Ctrl+F5 — без отладки. В уроках [«139. Многофайловая программа»](lesson-139-multi-file-project/README.md) — [«140. Защита заголовков от повторного включения»](lesson-140-multi-file-project-include-guard/README.md) открывайте `src/main.cpp`; скрипты подключают остальные
src/*.cpp и include/ автоматически. Каждый другой `main*.cpp` собирается отдельно.

Пример из корня репозитория в MSYS2 Bash на Windows:

```bash
bash scripts/build-windows.sh templates/lesson-126-class-templates/main.cpp
(cd templates/lesson-126-class-templates && ../../build/templates/lesson-126-class-templates/main.exe)
```

На Linux замените `build-windows.sh` на `build-linux.sh` и уберите расширение .exe.
Для файла с пробелом в имени (`main 2.cpp` в уроке [«126. Шаблоны классов»](../templates/lesson-126-class-templates/README.md)) заключайте путь в кавычки.
В F5/Ctrl+F5 рабочая папка — папка исходника; при ручном запуске её определяет терминал.
Первичная настройка IntelliSense и общая сборка описаны в [scripts/README.md](../scripts/README.md).

## Особенности учебных примеров

- Урок [«59. Изменение динамического массива»](lesson-059-dynamic-array-resize-delete-add-get/README.md) намеренно возвращает 1 после недопустимого индекса.
- `main.cpp` уроков [«133. Односвязный список: узлы и доступ»](lesson-133-singly-linked-list-part1/README.md) — [«134. Односвязный список: удаление»](lesson-134-singly-linked-list-part2/README.md) завершается на неперехваченном `out_of_range`.
- auto_ptr в уроке [«131. Виды умных указателей»](lesson-131-smart-pointers-types/README.md) — исторический пример, удалённый из C++17; библиотека может его не предоставлять.
- Урок [«141. Объединения `union`»](lesson-141-union/README.md) читает неактивные члены `union`; такой вывод нельзя считать переносимым стандартным C++.
- Урок [«145. Измерение времени выполнения»](lesson-145-measure-execution-time/README.md) содержит ожидания и вывод в терминал: полученное время не является чистым бенчмарком.

Изучайте ограничения в README перед запуском. Замена исходных примеров
современными средствами не подразумевается: дополнения объясняют продолжение темы.

[Все уроки](../LESSONS.md) · [Ввод-вывод](../io/README.md) · [Дополнения](additions/README.md)

## Курс и проверка

[Основы C++: начало плейлиста, установка среды](https://www.youtube.com/watch?v=kRcbYLK3OnQ&list=PLQOaTSbfxUtCrKs0nicOg2npJQYSPGO9r).
Для проекта используйте [свою настройку Windows/Linux](../README.md#требования).
Начальные уроки проверяются из корня: `python scripts/check-intro-lessons.py`
(на Linux — `python3`). Проверка создаёт файлы только в `build/`.
[Версии C++](../docs/cpp-versions.md) · [Источники](../docs/references.md).
