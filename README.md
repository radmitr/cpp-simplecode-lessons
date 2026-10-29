# cpp-simplecode-lessons

Упражнения и эксперименты по C++ на основе канала [#SimpleCode](https://www.youtube.com/@SimpleCodeIT) и плейлиста [«Основы C++»](https://www.youtube.com/playlist?list=PLQOaTSbfxUtCrKs0nicOg2npJQYSPGO9r). Личный учебный репозиторий, не официальный проект автора курса.

## Структура

- `basics/`, `oop/`, `stl/`, `multithreading/` — уроки по разделам.
- `multithreading/bonus/` — дополнительные темы по многопоточности после уроков 01–10.
- `examples/` — дополнительные примеры.
- `_template/` — заготовка урока.
- `scripts/` — общие скрипты сборки для Windows и Linux.

Ссылки на все уроки по разделам собраны в [LESSONS.md](LESSONS.md).
Пояснения к урокам многопоточности: [multithreading/README.md](multithreading/README.md).
Устройство сборки и выбор стандарта: [scripts/README.md](scripts/README.md).

## Требования

Нужно расширение VS Code **C/C++ от Microsoft**.

- **Windows:** MSYS2 MinGW-w64, компилятор и GDB в `C:/msys64/mingw64/bin/`, Bash и утилиты в `C:/msys64/usr/bin/`. Каталог MinGW должен быть в `PATH`, чтобы программы находили DLL. При другой установке измените пути в конфигурациях и `scripts/build-windows.sh`.
- **Linux:** `/usr/bin/g++`, `/usr/bin/gdb`, `/bin/bash`. На Ubuntu/Debian установите `build-essential` и `gdb`. Команда `locale charmap` должна показывать `UTF-8`.

На Windows и Linux по умолчанию используется C++17. Бонусы про std::jthread, семафор и барьер используют C++20; скрипты выбирают стандарт из cxx-standard.txt рядом с исходником. Для них нужны компилятор и стандартная библиотека с поддержкой соответствующих средств C++20. CMake не настроен.

## Сборка и запуск в VS Code

1. Откройте **корень репозитория** или **папку отдельного урока**.
2. Откройте нужный `.cpp` с `main()`. Обычно сборка использует активную вкладку.
3. Выберите действие:

- **Ctrl+Shift+B** — собрать.
- **F5** — собрать и запустить под GDB, конфигурация `C++: Run and Debug`.
- **Ctrl+F5** — собрать и запустить без отладки.
- **Terminal → Run Task… → C/C++: Run (No Build)** — запустить существующий бинарник без пересборки. После правок исходника это может быть старая версия программы.

Используются стандартные сочетания VS Code. Ввод программы выполняется во встроенном **Terminal**.

Задачи в `tasks.json`:

- `C/C++: Build` — общая сборка для Ctrl+Shift+B, F5 и Ctrl+F5. Скрипт `scripts/build-windows.sh` или `scripts/build-linux.sh` создаёт выходную папку и вызывает компилятор.
- `C/C++: Run (No Build)` — ручной запуск без сборки.

Эти две задачи одинаково устроены в корне, отдельных уроках и шаблоне. Базовые параметры подходят для Linux; блок `windows` переопределяет отличающиеся значения для Windows.

Параметры программы и отладчика находятся в `launch.json`; `preLaunchTask` ссылается на `C/C++: Build`. Пути программы и GDB заданы отдельно для Windows и Linux.

## Результаты сборки

При открытии корня и отдельного урока используется один каталог `build/` в корне со структурой исходников. Например:

```text
Windows: build/oop/lesson-113-oop-interfaces/main.exe
Linux:   build/oop/lesson-113-oop-interfaces/main
```

Для обычных уроков рабочая папка запуска — папка исходника: относительный `myFile.txt` относится к этому уроку. Учебные `myFile.txt` хранятся в Git и могут изменяться при записи. Каталог `build/` и локальные `.vscode/settings.json` игнорируются.

Общие скрипты добавляют `SimpleTimer.cpp` и `String.cpp` там, где они нужны. В уроках 139–140 собираются все `src/*.cpp` с заголовками из `include/`; результат соответствует `src/main.cpp`. Остальные `main2.cpp`, `main3.cpp` и т. п. — отдельные программы.

При копировании `_template` или переименовании урока обновите путь результата в его `tasks.json` и `launch.json`. Если меняется глубина вложенности, обновите также путь к `scripts/`. Конфигурации корня вычисляют путь автоматически. Для работы отдельного урока нужны общие скрипты из этого репозитория.

## Сборка из терминала

Из корня репозитория, на Linux:

```bash
bash scripts/build-linux.sh oop/lesson-113-oop-interfaces/main.cpp
./build/oop/lesson-113-oop-interfaces/main
```

На Windows из Git Bash или MSYS2 Bash:

```bash
bash scripts/build-windows.sh oop/lesson-113-oop-interfaces/main.cpp
./build/oop/lesson-113-oop-interfaces/main.exe
```

## Кириллица

Исходники и текстовые данные используют UTF-8. Обычные примеры на Windows настраивают консоль через `SetConsoleCP(CP_UTF8)` и `SetConsoleOutputCP(CP_UTF8)`. Дополнительный профиль терминала не требуется. На Linux нужен терминал с UTF-8.

В `basics/lesson-118-file-io-fstream/main3.cpp` используются широкие потоки: `setupWideStandardIO()` вызывает `_setmode` на Windows и `std::setlocale(LC_ALL, "")` на Linux. Кодировка файла для `wfstream` задаётся отдельно через `imbue`.

## Особенности примеров

В некоторых учебных примерах предусмотрены ошибки или незавершающееся выполнение:

- `basics/lesson-059-dynamic-array-resize-delete-add-get/main.cpp` возвращает 1 после обработки недопустимого индекса.
- `basics/lesson-133-singly-linked-list-part1/main.cpp` и `basics/lesson-134-singly-linked-list-part2/main.cpp` вызывают неперехваченное `std::out_of_range` при обращении к `list[1000]`.
- `multithreading/lesson-02-thread-param/main.cpp` содержит бесконечный цикл.

В старых примерах используются устаревшие `auto_ptr`, `random_shuffle` и `codecvt`; их доступность зависит от компилятора и стандартной библиотеки. В уроке 139 остаётся предупреждение о строковом литерале в параметре `char*`.
