# Основы C++

Уроки исходного курса с сохранёнными номерами. Это выборка учебных примеров,
а не полный курс с нуля: пропуски номеров не означают потерю файлов.
Пояснения к вариантам main*.cpp, ожидаемому поведению и ограничениям находятся
в README каждого урока. Новые темы размещаются в [bonus](bonus/README.md).

## Как изучать

Сначала нужны переменные, условия, циклы, функции, ссылки и указатели.
Для шаблонов классов и владения памятью полезны [уроки ООП](../LESSONS.md#ооп).
Тематический порядок ниже дополняет исходную нумерацию курса.

- Массивы 58–59 изучайте после указателей; обработка ошибки в 59 использует исключения 120–123.
- Указатели на функции 65 → std::function 142 → лямбды 143–144 → функторы 146 → предикаты 147.
- [Файлы и потоки 115–119](../io/README.md) → исключения 120–123.
- Шаблоны 126–128 → умные указатели 130–132 → список 133–135.
- [constexpr/consteval](bonus/01-constexpr-consteval/README.md) — после функций; перед изучением статической рефлексии.
- [RAII](bonus/02-raii/README.md) — после деструкторов и try/catch; связывает файлы, память и исключения.

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

- [120. Обработка исключений: try и catch](lesson-120-exception-handling-try-catch/README.md).
- [121. Выбрасывание исключений: throw](lesson-121-exception-throw/README.md).
- [122. Несколько обработчиков catch](lesson-122-multiple-catch-blocks/README.md).
- [123. Собственные классы исключений](lesson-123-custom-exception-class/README.md).

## Типы и объявления

- [124. Перечисления enum](lesson-124-enum-types/README.md).
- [125. Пространства имён](lesson-125-namespaces/README.md).
- [129. struct и class](lesson-129-structures-struct-vs-class/README.md).
- [136. Вывод типа через auto](lesson-136-auto-keyword/README.md).
- [137. Цикл по диапазону](lesson-137-range-based-for-loop/README.md).
- [138. Псевдонимы типов: typedef](lesson-138-typedef-keyword/README.md).
- [141. Объединения union](lesson-141-union/README.md).

## Шаблоны

- [126. Шаблоны классов](lesson-126-class-templates/README.md).
- [127. Наследование шаблонных классов](lesson-127-class-templates-inheritance/README.md).
- [128. Специализация шаблонов](lesson-128-class-templates-specialization/README.md).

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

Основные уроки используют C++17. Бонус constexpr/consteval выбирает C++20
через cxx-standard.txt. На Ubuntu 22.04 для этих бонусов подходит GCC 11;
GCC 16 и C++26 нужны для [самостоятельного раздела рефлексии](../bonus/reflection/README.md).

В VS Code откройте исходник с main(): Ctrl+Shift+B собирает, F5 запускает
под GDB. В уроках 139–140 открывайте src/main.cpp; скрипты подключают остальные
src/*.cpp и include/ автоматически. Каждый другой main*.cpp собирается отдельно.

Пример из корня репозитория в MSYS2 Bash на Windows:

```bash
bash scripts/build-windows.sh basics/lesson-126-class-templates/main.cpp
(cd basics/lesson-126-class-templates && ../../build/basics/lesson-126-class-templates/main.exe)
```

На Linux замените build-windows.sh на build-linux.sh и уберите расширение .exe.
Для файла с пробелом в имени (main 2.cpp в уроке 126) заключайте путь в кавычки.
В F5 рабочая папка — папка исходника; при ручном запуске её определяет терминал.
Первичная настройка IntelliSense и общая сборка описаны в [scripts/README.md](../scripts/README.md).

## Особенности учебных примеров

- Урок 59 намеренно возвращает 1 после недопустимого индекса.
- main.cpp уроков 133–134 завершается на неперехваченном out_of_range.
- auto_ptr в уроке 131 — исторический пример, удалённый из C++17; библиотека может его не предоставлять.
- Урок 141 читает неактивные члены union; такой вывод нельзя считать переносимым стандартным C++.
- Урок 145 содержит ожидания и вывод в терминал: полученное время не является чистым бенчмарком.

Изучайте ограничения в README перед запуском. Замена исходных примеров
современными средствами не подразумевается: бонусы объясняют продолжение темы.

[Все уроки](../LESSONS.md) · [Ввод-вывод](../io/README.md) · [Бонусы](bonus/README.md)
