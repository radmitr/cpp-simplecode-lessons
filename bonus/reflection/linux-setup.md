# Ubuntu 22.04: GCC 16 отдельно от системного компилятора

Эта инструкция подготовлена для последующей проверки пользователем на Linux.
В текущем окружении примеры проверяются на Windows/MinGW64; успешный запуск
Windows не является подтверждением сборки GCC или запуска программ на Ubuntu.

## Размещение и место

Исходники и временную сборку GCC разместите в домашнем разделе /home,
а готовый компилятор установите в /opt/gcc-16. На разделе с /opt потребуется
место только для готовой установки. После проверки установленного компилятора
исходники и каталог сборки можно удалить отдельно; удаление каталога установки
удалит сам компилятор и его библиотеки.

Проверьте оба раздела:

```bash
df -h "$HOME" /opt
```

Временная сборка существенно больше готовой установки. Точный размер зависит
от параметров, отладочных данных и bootstrap; оставьте запас и следите за
свободным местом. Число параллельных процессов ограничивается также памятью.
Пример ниже использует два процесса и bootstrap-lean, удаляющий ненужные стадии.

## Зависимости и исходники

Системный GCC 11 достаточно новый для сборки C/C++-части GCC 16. Он остаётся
системным компилятором. Следующие команды предназначены для выполнения позже
на Ubuntu, а не для терминала Windows:

```bash
sudo apt update
sudo apt install build-essential curl xz-utils flex bison texinfo \
    libgmp-dev libmpfr-dev libmpc-dev zlib1g-dev

mkdir -p "$HOME/src" "$HOME/build/gcc-16.2.0"
cd "$HOME/src"
curl --fail --location \
    https://sourceware.org/pub/gcc/releases/gcc-16.2.0/gcc-16.2.0.tar.xz \
    --output gcc-16.2.0.tar.xz
tar -xf gcc-16.2.0.tar.xz
```

Каталог сборки должен быть отдельным от исходников и установки. При повторной
сборке с другими параметрами используйте новый пустой каталог сборки.

## Сборка и установка

```bash
cd "$HOME/build/gcc-16.2.0"
"$HOME/src/gcc-16.2.0/configure" \
    --prefix=/opt/gcc-16 \
    --enable-languages=c,c++ \
    --disable-multilib

make -j2 BOOT_CFLAGS='-O2 -g0' bootstrap-lean
sudo make install-strip

/opt/gcc-16/bin/g++ --version
```

--enable-languages ограничивает набор языков, --disable-multilib исключает
дополнительные 32-битные варианты. Bootstrap проверяет сборку компилятором самого
себя; bootstrap-lean сокращает пиковое хранение промежуточных стадий.
Установка требует прав на /opt; конфигурация и сборка выполняются обычным
пользователем. Официальные подробности: [требования](https://gcc.gnu.org/install/prerequisites.html),
[конфигурация](https://gcc.gnu.org/install/configure.html),
[сборка](https://gcc.gnu.org/install/build.html).

## Проверка рефлексии и библиотек

Вернитесь в корень этого репозитория:

```bash
export CXX_MODERN=/opt/gcc-16/bin/g++
bash scripts/build-linux.sh bonus/reflection/06-toolchain/main.cpp
./build/bonus/reflection/06-toolchain/main

bash scripts/build-linux.sh bonus/reflection/11-data-members/main.cpp
ldd ./build/bonus/reflection/11-data-members/main
./build/bonus/reflection/11-data-members/main
```

Общий build-linux.sh определяет каталог libstdc++.so.6 через выбранный g++
и записывает rpath в исполняемый файл. Поэтому runtime должен находить библиотеку
установленного GCC, а не случайно выбирать старую системную. Каталог не задан
как lib или lib64 вручную: расположение определяет сам компилятор.

Если уже сам /opt/gcc-16/bin/g++ не запускается из-за библиотек, сначала
проверьте его ldd. Временную настройку поиска делайте только для этого запуска
или отдельного терминала; не заменяйте системные libstdc++ и не создавайте на них
глобальные симлинки. Настройка rpath приложения не исправляет зависимости
исполняемого файла самого компилятора. [Поиск libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dynamic_or_shared.html).

## Полная проверка на Ubuntu — что ещё нужно сделать

1. Собрать и установить GCC в указанных каталогах; записать версию и платформу.
2. Установить nlohmann/json по [инструкции зависимости](dependencies.md).
   Он нужен также для JSON-примеров io/bonus.
3. Проверить обычные C++17/20-бонусы системным GCC 11:

   ```bash
   python3 scripts/check-bonuses.py --portable-only
   ```

4. Запустить весь набор с новым компилятором для современных уроков:

   ```bash
   CXX_MODERN=/opt/gcc-16/bin/g++ python3 scripts/check-bonuses.py
   ```

5. Обновить базу IntelliSense с тем же выбором компилятора:

   ```bash
   CXX_MODERN=/opt/gcc-16/bin/g++ bash scripts/generate-compile-commands.sh
   ```

6. Проверить F5 из корня и отдельной папки C++26-урока, затем отдельно
   многофайловый урок 22 через src/main.cpp. Нужен установленный GDB.
7. Проверить ldd готового приложения: нет not found, выбирается ожидаемая
   libstdc++. Сохранить build/bonus-checks/report.json и проверить число failed.
8. При необходимости отдельно запустить Linux-диагностику ASan/UBSan из
   basics/bonus/29-diagnostics/run-sanitizers.sh.

До выполнения этих шагов статус Linux остаётся «подготовлено, запуск не проверен».
После изменения CXX/CXX_MODERN базу IntelliSense нужно генерировать заново.

[К урокам](README.md)
