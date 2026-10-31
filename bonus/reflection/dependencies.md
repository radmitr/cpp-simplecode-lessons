# Windows, компиляторы и зависимость JSON

## Windows / MinGW64

Обычные уроки 01–05 используют C++17; 06–30 требуют GCC 16+ с заголовком meta
и -freflection. Проверенная локальная установка: MSYS2 MinGW64 GCC 16.2.0.
Сборка использует C:/msys64/mingw64/bin/g++.exe, отладка — соседний gdb.exe.
Этот каталог должен находиться в PATH также при запуске exe: там лежат DLL
стандартной библиотеки. Не смешивайте библиотеки MINGW64/UCRT64 разных установок.

В терминале MSYS2 MinGW64:

```bash
g++ --version
bash scripts/build-windows.sh bonus/reflection/06-toolchain/main.cpp
./build/bonus/reflection/06-toolchain/main.exe
python scripts/check-bonuses.py --section bonus/reflection
```

После выбора другого компилятора задайте CXX_MODERN полным путём и повторите
генерацию IntelliSense. Резервные настройки VS Code и база содержат тот же
стандарт и компилятор. Парсер редактора может отставать от нового синтаксиса;
фактическую корректность определяют компилятор и сохранённые проверки.

## nlohmann/json

Зависимость нужна только урокам 28–29. Остальные уроки рефлексии от неё не зависят.
Используется обычный публичный интерфейс библиотеки; локальная проверка выполняется
с версией 3.12.0. [Официальный проект и лицензия MIT](https://github.com/nlohmann/json).

Ubuntu 22.04:

```bash
sudo apt install nlohmann-json3-dev
```

MSYS2 MinGW64:

```bash
pacman -S mingw-w64-x86_64-nlohmann-json
```

Можно обойтись без системной установки: из корня в Bash на Windows или Linux
скачать официальный одиночный заголовок в игнорируемый каталог:

```bash
mkdir -p build/dependencies/include/nlohmann
curl --fail --location \
    https://raw.githubusercontent.com/nlohmann/json/v3.12.0/single_include/nlohmann/json.hpp \
    --output build/dependencies/include/nlohmann/json.hpp
sha256sum build/dependencies/include/nlohmann/json.hpp
```

SHA-256 указанного файла версии 3.12.0:

```text
aaf127c04cb31c406e5b04a63f1ae89369fccde6d8fa7cdda1ed4f32dfc5de63
```

include-library.txt рядом с исходником содержит nlohmann-json. Если локальный
заголовок найден, общие скрипты добавляют его как system include; иначе используется
системная установка. Генератор IntelliSense использует тот же путь. После добавления
или удаления локальной копии обновите базу. Заголовок не копируется в Git и не
загружается автоматически во время обычной сборки.

[Подготовка Linux](linux-setup.md) · [К урокам](README.md)
