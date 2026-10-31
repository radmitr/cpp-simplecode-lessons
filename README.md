# cpp-simplecode-lessons

Упражнения и эксперименты по C++ на основе канала [#SimpleCode](https://www.youtube.com/@SimpleCodeIT) и плейлиста [«Основы C++»](https://www.youtube.com/playlist?list=PLQOaTSbfxUtCrKs0nicOg2npJQYSPGO9r). Личный учебный репозиторий, не официальный проект автора курса.

## Структура

- [basics/](basics/README.md) — основы языка и [бонусы](basics/bonus/README.md).
- [io/](io/README.md) — ввод-вывод, потоки и файлы; уроки 115–119 и [бонусы](io/bonus/README.md).
- `oop/`, `stl/`, `multithreading/` — уроки по разделам.
- `bonus/` — дополнительные направления вне курса: [рефлексия](bonus/reflection/README.md), [сети на Windows/Linux](bonus/networking/README.md).
- `bonus/databases/postgresql/` — [20 уроков PostgreSQL из C++](bonus/databases/postgresql/README.md), Windows/MinGW64 и Linux.
- `multithreading/bonus/` — дополнительные темы по многопоточности после уроков 01–10.
- `examples/` — дополнительные примеры.
- `_template/` — заготовка урока.
- `scripts/` — общие скрипты сборки для Windows и Linux.

Ссылки на все уроки по разделам собраны в [LESSONS.md](LESSONS.md).
Пояснения к основам: [basics/README.md](basics/README.md); к потокам и файлам: [io/README.md](io/README.md).
Пояснения к урокам многопоточности: [multithreading/README.md](multithreading/README.md).
Устройство сборки и выбор стандарта: [scripts/README.md](scripts/README.md).

## Требования

Нужно расширение VS Code **C/C++ от Microsoft**.

- **Windows:** MSYS2 MinGW-w64, компилятор и GDB в `C:/msys64/mingw64/bin/`, Bash и утилиты в `C:/msys64/usr/bin/`. Каталог MinGW должен быть в `PATH`, чтобы программы находили DLL. При другой установке измените пути в конфигурациях, `scripts/build-windows.sh` и `scripts/generate-compile-commands.sh`.
- **Linux:** `/usr/bin/g++`, `/usr/bin/gdb`, `/bin/bash`. На Ubuntu/Debian установите `build-essential` и `gdb`. Команда `locale charmap` должна показывать `UTF-8`.

На Windows и Linux по умолчанию используется C++17. cxx-standard.txt рядом
с исходником выбирает C++17/20/23/26; gcc-min-version.txt при необходимости
задаёт минимальную версию GCC. Бонусы основ и IO в основном рассчитаны на GCC 11
и C++17/20. Современный IO-урок format/print требует GCC 14+, рефлексия C++26 —
GCC 16+ и -freflection. Для них на Linux используется CXX_MODERN, по умолчанию
/opt/gcc-16/bin/g++; остальные уроки используют /usr/bin/g++ (или CXX).
Подготовка отдельного GCC в /home с установкой в /opt описана в
[инструкции Linux](bonus/reflection/linux-setup.md). Linux-проверка новых бонусов
ещё предстоит пользователю; настройки Windows/Linux подготовлены. CMake не настроен.

В [бонусе про ThreadSanitizer](multithreading/bonus/26-thread-sanitizer/)
диагностика гонки данных запускается отдельным скриптом на Linux/WSL
с компилятором и библиотекой TSan. Обычная сборка F5 её не включает.

[Сетевые уроки](bonus/networking/README.md) используют WinSock на Windows
и POSIX-сокеты на Linux. Для HTTP/HTTPS нужна libcurl; зависимости и запуск
клиента с сервером описаны в README раздела.
Для примеров Boost.Asio и WebSocket нужны также заголовки Boost;
уроки включают локальные проверки IPv6, повторов, файлов и асинхронных операций.

[Уроки PostgreSQL](bonus/databases/postgresql/README.md) используют libpq и C++17.
В разделе описаны зависимости для MinGW64/Linux и запуск отдельного учебного
сервера на порту 55432; основной PostgreSQL компьютера можно оставить работающим.

## Сборка и запуск в VS Code

1. Откройте **корень репозитория** или **папку отдельного урока**.
2. Откройте нужный `.cpp` с `main()`. Обычно сборка использует активную вкладку.
3. Выберите действие:

- **Ctrl+Shift+B** — собрать.
- **F5** — собрать и запустить под GDB, конфигурация `C++: Run and Debug`.
- **Ctrl+F5** — собрать и запустить без отладки.
- **Terminal → Run Task… → C/C++: Update IntelliSense** — создать или обновить настройки IntelliSense по необходимости.
- **Terminal → Run Task… → C/C++: Run (No Build)** — запустить существующий бинарник без пересборки. После правок исходника это может быть старая версия программы.

Используются стандартные сочетания VS Code. Ввод программы выполняется во встроенном **Terminal**.

Задачи в `tasks.json`:

- `C/C++: Build` — общая сборка для Ctrl+Shift+B, F5 и Ctrl+F5. Скрипт `scripts/build-windows.sh` или `scripts/build-linux.sh` создаёт выходную папку и вызывает компилятор.
- `C/C++: Update IntelliSense` — ручное обновление общей базы и локальных конфигураций IntelliSense без компиляции. Не требует открытого `.cpp`.
- `C/C++: Run (No Build)` — ручной запуск без сборки.

Эти три задачи одинаково устроены в корне, отдельных уроках и шаблоне. Базовые параметры подходят для Linux; блок `windows` переопределяет отличающиеся значения для Windows.

Параметры программы и отладчика находятся в `launch.json`; `preLaunchTask` ссылается на `C/C++: Build`. Пути программы и GDB заданы отдельно для Windows и Linux.

## IntelliSense и стандарт C++

После клонирования выполните **Terminal → Run Task… → C/C++: Update IntelliSense**.
Задача запускает генератор, который создаёт
`build/compile_commands.json` и локальные `.vscode/c_cpp_properties.json`
в папках уроков, примеров и шаблона с `.vscode/tasks.json`.
Корневая и локальные конфигурации подключают одну общую базу: она задаёт
компилятор, пути заголовков и выбранный стандарт C++ для каждого `.cpp`
по `cxx-standard.txt` рядом с исходником. Современные уроки учитывают CXX_MODERN и дополнительные флаги из общих настроек компилятора. Настройка работает при открытии
корня репозитория и отдельных уроков внутри него, без пользовательских
настроек VS Code.

База и сгенерированные локальные конфигурации игнорируются Git. Повторяйте
задачу после добавления, удаления или переименования исходников, изменения
стандарта, компилятора или флагов сборки. Обычное редактирование кода не требует
повторной генерации. Ctrl+Shift+B, F5 и Ctrl+F5 выполняют сборку без генератора.
Файлы с неизменившимся содержимым не перезаписываются.
Для запуска генератора из терминала в корне на Linux или в MSYS2 Bash на Windows выполните:

```bash
bash scripts/generate-compile-commands.sh
```

Генератор сохраняет существующие пользовательские конфигурации. Созданные
им файлы помечены комментарием с контрольной суммой; после ручного изменения
такого файла генератор также оставляет его как пользовательский. Чтобы
вернуть автоматическое управление, удалите локальный `c_cpp_properties.json`
и выполните задачу `C/C++: Update IntelliSense` заново.

База содержит локальные пути, поэтому после переноса проекта или
переключения между Linux и Windows выполните задачу `C/C++: Update IntelliSense`.
Простое открытие папки настройки не создаёт и не обновляет. До первой
генерации корень использует резервный C++17, а отдельно открытый урок —
обычные настройки расширения. Сгенерированные локальные конфигурации имеют
резервный стандарт соответствующего урока. Если после генерации остались
старые подчёркивания, выполните `C/C++: Reset IntelliSense Database` из
палитры команд VS Code.

Активная конфигурация IntelliSense должна соответствовать системе: `Win32`
для Windows и `Linux` для Linux. Если на Windows появляется предупреждение
о `/usr/bin/g++`, нажмите название конфигурации в строке состояния и выберите
`Win32`; в ней указан MinGW `C:/msys64/mingw64/bin/g++.exe`.

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

В `io/lesson-118-file-io-fstream/main3.cpp` используются широкие потоки: `setupWideStandardIO()` вызывает `_setmode` на Windows и `std::setlocale(LC_ALL, "")` на Linux. Кодировка файла для `wfstream` задаётся отдельно через `imbue`.

## Особенности примеров

В уроке `basics/lesson-141-union/main.cpp` читаются неактивные члены union;
такое поведение в общем случае не определено стандартом C++. Ограничения описаны
в [README урока](basics/lesson-141-union/README.md).

В некоторых учебных примерах предусмотрены ошибки или незавершающееся выполнение:

- `basics/lesson-059-dynamic-array-resize-delete-add-get/main.cpp` возвращает 1 после обработки недопустимого индекса.
- `basics/lesson-133-singly-linked-list-part1/main.cpp` и `basics/lesson-134-singly-linked-list-part2/main.cpp` вызывают неперехваченное `std::out_of_range` при обращении к `list[1000]`.
- `multithreading/lesson-02-thread-param/main.cpp` содержит бесконечный цикл.

В старых примерах используются устаревшие `auto_ptr`, `random_shuffle` и `codecvt`; их доступность зависит от компилятора и стандартной библиотеки. В уроке 139 остаётся предупреждение о строковом литерале в параметре `char*`.
