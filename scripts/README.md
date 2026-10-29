# Скрипты сборки

build-linux.sh и build-windows.sh собирают один выбранный .cpp.
Запускайте их через Bash, передавая путь к существующему файлу.

Из корня репозитория, Linux:

~~~bash
bash scripts/build-linux.sh multithreading/lesson-10-unique-lock/main.cpp
./build/multithreading/lesson-10-unique-lock/main
~~~

Из корня репозитория, Windows / MSYS2 Bash:

~~~bash
bash scripts/build-windows.sh multithreading/lesson-10-unique-lock/main.cpp
./build/multithreading/lesson-10-unique-lock/main.exe
~~~

## Компилятор и результат

Linux использует /usr/bin/g++, Windows — C:/msys64/mingw64/bin/g++.exe.
Скрипт определяет корень проекта по собственному расположению.
Поэтому путь к исходнику может быть абсолютным или относительным к текущей папке.
Файлы за пределами репозитория скрипт отклоняет.

Результат сохраняется в build/ с тем же относительным путём, что у исходника.
main.cpp и main2.cpp собираются отдельно. Если рядом есть SimpleTimer.cpp
или String.cpp, скрипт добавляет их как вспомогательные исходники.
Для src/main.cpp с соседней папкой include/ собираются все .cpp из src/.

## Стандарт C++

По умолчанию выбирается c++17. Если в папке исходника существует
cxx-standard.txt, скрипт читает стандарт из него.
Файл должен содержать одну строку c++17 или c++20 без пробелов.
Другие значения вызывают ошибку; пример для C++20 находится в
[бонусе про jthread](../multithreading/bonus/06-jthread-stop-token/).

~~~bash
standard=c++17
if [[ -f $source_dir/cxx-standard.txt ]]; then
    standard=$(<"$source_dir/cxx-standard.txt")
    standard=${standard//$'\r'/}
    case $standard in
        c++17|c++20) ;;
        *) printf 'Unsupported C++ standard: %s\n' "$standard" >&2; exit 2 ;;
    esac
fi
~~~

- [[ -f ... ]] проверяет наличие обычного файла.
- $(<"...") читает файл, как $(cat "..."), и убирает завершающие символы LF.
- ${standard//$'\r'/} удаляет символы CR, которые могут остаться от окончаний CRLF.
- c++17|c++20) ;; — пустая ветка case для двух разрешённых значений.
- *) — ветка для остальных значений; ;; завершает ветку.
- "-std=$standard" передаёт выбранный стандарт компилятору.

В Windows-файле одна строка может оканчиваться на CRLF (\r\n).
После подстановки команд останется CR (\r); отдельная замена удаляет и его.
Файл на диске при чтении не изменяется.

## Связь с VS Code

Задача C/C++: Build вызывает нужный скрипт для активного файла.
При копировании урока проверьте пути к scripts/ и build/ в его
.vscode/tasks.json и .vscode/launch.json: они зависят от глубины папки.

Все примеры команд сборки приведены для Bash. Сам Bash запускает компилятор,
а C++ выполняется в собранной программе.
