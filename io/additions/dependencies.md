# Зависимости дополнений по вводу-выводу

Большинство уроков используют стандартную библиотеку C++17 и требуют GCC 11+.
В [работе с UTF-8 и `char8_t`](15-utf8/README.md) используется C++20.
Дополнительные требования есть у [JSON](17-json/README.md) и
[форматирования и печати](05-format-and-print/README.md).

## JSON

Уроку [JSON: библиотека, типы и обязательные поля](17-json/README.md)
нужен `nlohmann/json`.

Ubuntu:

```bash
sudo apt install nlohmann-json3-dev
```

MSYS2 MinGW64:

```bash
pacman -S mingw-w64-x86_64-nlohmann-json
```

Без системной установки можно использовать официальный одиночный заголовок
в `build/dependencies/include`. Версия, URL, SHA-256 и правила выбора описаны
в [инструкции JSON](../../additions/reflection/dependencies.md#nlohmannjson).

## Современные format/print

Урок [`std::format` и `std::print`](05-format-and-print/README.md)
собирается как C++23 и требует GCC/libstdc++ 14+.
На Linux общий скрипт использует `CXX_MODERN`, по умолчанию
`/opt/gcc/16/bin/g++`. Обычные уроки продолжают использовать системный `g++`.

[Сборка отдельного GCC на Ubuntu](../../additions/reflection/linux-setup.md).

## Временные файлы

Файловые примеры с [`LessonWorkspace`](common/workspace.hpp) создают уникальную
временную папку и удаляют только её. `CPP_LESSON_WORK_DIR` задаёт родительский
каталог; проверочный скрипт выбирает каталог внутри `build/`.
[Явный бинарный формат](18-portable-binary/README.md) создаёт `point-v1.bin`
в рабочей папке программы.

Симлинки в [операциях с файлами и каталогами](14-filesystem-operations/README.md)
могут быть недоступны на Windows без соответствующих прав: пример выводит
`symlink unavailable`, остальные операции продолжаются.

[К урокам](README.md)
