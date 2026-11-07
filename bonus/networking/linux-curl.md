# Linux: отдельная установка curl с HTTP/2 и HTTP/3

Утилита `curl` выполняет запросы из терминала, а библиотека `libcurl` используется
C++-программами. Для HTTP/3 библиотека должна быть собрана с QUIC-транспортом;
одного нового заголовка или номера версии недостаточно.

## Размещение и зависимости

Каждый комплект устанавливается в отдельный каталог. В нём находятся
`curl`/`libcurl` и собственные OpenSSL, nghttp2, nghttp3 и ngtcp2:

```text
/opt/curl/
├── 8.23.0/         ← bin/curl, include/, lib/ и зависимости этого выпуска
├── 8 -> 8.23.0    ← выбранный выпуск ветки 8
└── current -> 8   ← выбранная основная версия
```

Исходники, сборка и временные файлы остаются в `/home`. Системные `curl`,
`libcurl` и OpenSSL обслуживаются APT отдельно. Команды ниже не меняют
`/usr/bin/curl`, глобальные `PATH`, `LD_LIBRARY_PATH`, `ldconfig` или профили.

Для Ubuntu/Debian нужны инструменты сборки и заголовки zlib:

```bash
sudo apt-get install build-essential pkg-config perl curl xz-utils ca-certificates zlib1g-dev
sudo install -d -m 755 -o "$USER" -g "$(id -gn)" /opt/curl
```

В этой схеме каталог принадлежит текущему пользователю: сама сборка и установка
внутри него выполняются без `sudo`. Временная сборка требует больше места,
чем готовая установка; проверьте `df -h "$HOME" /opt`. Значение `-j6` ниже
подберите по памяти и числу процессоров. Дополнительные функции curl могут
зависеть от автоматически найденных системных библиотек; например, для Brotli
нужен `libbrotli-dev`. Он не обязателен для HTTP/2 и HTTP/3.

## Исходники с закреплёнными версиями

Для приведённого комплекта используются curl 8.23.0, OpenSSL 3.5.9,
nghttp2 1.71.0, nghttp3 1.19.0 и ngtcp2 1.26.0. Версии закреплены
для воспроизводимой сборки.

Скачайте официальные архивы в новый каталог и проверьте SHA-256 перед распаковкой:

```bash
mkdir -p "$HOME/src/curl-sdk-8.23.0" "$HOME/build/curl-8.23.0" "$HOME/tmp/curl-8.23.0"
cd "$HOME/src/curl-sdk-8.23.0"
curl --fail --location --output openssl-3.5.9.tar.gz \
    https://github.com/openssl/openssl/releases/download/openssl-3.5.9/openssl-3.5.9.tar.gz
curl --fail --location --output nghttp2-1.71.0.tar.xz \
    https://github.com/nghttp2/nghttp2/releases/download/v1.71.0/nghttp2-1.71.0.tar.xz
curl --fail --location --output nghttp3-1.19.0.tar.xz \
    https://github.com/ngtcp2/nghttp3/releases/download/v1.19.0/nghttp3-1.19.0.tar.xz
curl --fail --location --output ngtcp2-1.26.0.tar.xz \
    https://github.com/ngtcp2/ngtcp2/releases/download/v1.26.0/ngtcp2-1.26.0.tar.xz
curl --fail --location --output curl-8.23.0.tar.xz \
    https://github.com/curl/curl/releases/download/curl-8_23_0/curl-8.23.0.tar.xz
cat > SHA256SUMS <<'SUMS'
603f5602e2eef00d77fbd429d34dcd5822bb301757a1bc9cdb24c670f1eb859a  openssl-3.5.9.tar.gz
c0f55121d88650e4b9227aec28cebaf664d2417ca60fe70be0f8d38829f52116  nghttp2-1.71.0.tar.xz
228e17f5cc3d4de7bfced9912bd09de30e7f45741cc47503cf88d3fa9209e155  nghttp3-1.19.0.tar.xz
7804aa0fa1c39942ba322a90805824c37231f7675b08d0c3cc4332858a7b085e  ngtcp2-1.26.0.tar.xz
8dadd7d2536a314f982ad05a651b713f426bf7d02cc2c76cffb9796f2218e6c5  curl-8.23.0.tar.xz
SUMS
sha256sum --check SHA256SUMS
```

Продолжайте только после успешной проверки всех пяти архивов:

```bash
for archive in openssl-3.5.9.tar.gz nghttp2-1.71.0.tar.xz nghttp3-1.19.0.tar.xz \
    ngtcp2-1.26.0.tar.xz curl-8.23.0.tar.xz; do
    tar -xf "$archive"
done
```

## Сборка и установка

Сохраните следующий сценарий в файл `build.sh` рядом с распакованными каталогами.
Он выбирает конечный `--prefix` с начала сборки, а зависимости последовательно
устанавливаются туда же. `rpath` — записанный в ELF-файле путь поиска библиотек:
он позволяет находить собственные зависимости без глобального `LD_LIBRARY_PATH`.
Уже установленный выпуск сценарий не перезаписывает; для нового выпуска
подготовьте новый каталог, версии исходников и конечный префикс.

```bash
#!/usr/bin/env bash
set -euo pipefail

source_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
build_root=${CURL_BUILD_ROOT:-$HOME/build/curl-8.23.0}
prefix=/opt/curl/8.23.0
export TMPDIR=${CURL_BUILD_TMPDIR:-$HOME/tmp/curl-8.23.0}
export PATH=/usr/bin:/bin
export CC=/usr/bin/gcc CXX=/usr/bin/g++
export CFLAGS='-O2 -g0' CXXFLAGS='-O2 -g0'
export PKG_CONFIG_PATH="$prefix/lib/pkgconfig"
export LDFLAGS="-L$prefix/lib -Wl,-rpath,$prefix/lib"
export CPPFLAGS="-I$prefix/include"
jobs=${CURL_BUILD_JOBS:-6}
if [[ ! $jobs =~ ^[1-9][0-9]*$ ]]; then
    printf 'CURL_BUILD_JOBS must be a positive integer.\n' >&2
    exit 2
fi
if [[ ! -d /opt/curl || ! -w /opt/curl ]]; then
    printf 'Create writable /opt/curl before building; see README.md.\n' >&2
    exit 2
fi
if [[ -e $prefix/bin/curl || -L $prefix ]]; then
    printf 'Refusing to overwrite an existing installation: %s\n' "$prefix" >&2
    exit 2
fi
mkdir -p -- "$build_root" "$TMPDIR" "$prefix/lib"
trap 'status=$?; printf "%s\n" "$status" > "$build_root/build.exit-code"' EXIT

phase() {
    printf '%s\n' "$1" > "$build_root/current-phase"
    printf '\nBuilding %s\n' "$1"
    mkdir -p -- "$build_root/$1"
    cd -- "$build_root/$1"
}

phase openssl
"$source_root/openssl-3.5.9/Configure" --prefix="$prefix" --openssldir="$prefix/ssl" \
    --libdir=lib shared no-tests "-Wl,-rpath,$prefix/lib"
make -j"$jobs"
make install_sw

phase nghttp2
"$source_root/nghttp2-1.71.0/configure" --prefix="$prefix" \
    --enable-lib-only --enable-shared --disable-static
make -j"$jobs"
make install

phase nghttp3
"$source_root/nghttp3-1.19.0/configure" --prefix="$prefix" \
    --enable-lib-only --enable-shared --disable-static
make -j"$jobs"
make install

phase ngtcp2
"$source_root/ngtcp2-1.26.0/configure" --prefix="$prefix" \
    --enable-lib-only --with-openssl --enable-shared --disable-static
make -j"$jobs"
make install

phase curl
"$source_root/curl-8.23.0/configure" --prefix="$prefix" \
    --with-openssl="$prefix" --with-nghttp2="$prefix" \
    --with-nghttp3="$prefix" --with-ngtcp2="$prefix" \
    --with-ca-bundle=/etc/ssl/certs/ca-certificates.crt \
    --without-libpsl --enable-shared --disable-static
make -j"$jobs"
make install
"$prefix/bin/curl" --version > "$build_root/curl-version.txt"
grep -q '^curl 8\.23\.0 ' "$build_root/curl-version.txt"
grep -q 'Features:.*HTTP2.*HTTP3' "$build_root/curl-version.txt"
printf 'complete\n' > "$build_root/current-phase"
cat "$build_root/curl-version.txt"
```

Запустите сценарий из обычного терминала:

```bash
bash "$HOME/src/curl-sdk-8.23.0/build.sh"
```

`CURL_BUILD_ROOT`, `CURL_BUILD_TMPDIR` и `CURL_BUILD_JOBS` при необходимости
переопределяют каталоги сборки/временных файлов и число задач.
`--without-libpsl` отключает необязательную зависимость; `--with-ca-bundle`
оставляет доверенные сертификаты из системного пакета `ca-certificates`.
OpenSSL собирается с `no-tests`; приведённый сценарий не запускает его
официальную тестовую систему. Наличие HTTP/3 нужно проверять отдельно.

## Проверка и ссылки выбора

Сначала проверьте готовый выпуск и зависимости:

```bash
/opt/curl/8.23.0/bin/curl --version
ldd /opt/curl/8.23.0/lib/libcurl.so.4
```

В строке `Features` должны присутствовать `HTTP2` и `HTTP3`; в `ldd` не должно
быть `not found`, а частные OpenSSL/QUIC-библиотеки должны находиться в этом
выпуске. После проверки создайте ссылки:

```bash
ln -sT 8.23.0 /opt/curl/8
ln -sT 8 /opt/curl/current
readlink -f /opt/curl/current
/opt/curl/current/bin/curl --version
```

Для переключения ветки на другой уже установленный выпуск замените `8.23.0`
в `ln -sTf 8.23.0 /opt/curl/8`. Для основной версии используйте
`ln -sTf 8 /opt/curl/current`. Если родитель принадлежит root, эти операции
требуют `sudo`. Значение `current` выбирает пользователь; оно не обновляется само.

## Подключение к примерам

Маркер `curl` в `link-libraries.txt` включает выбор библиотеки только для нужного
урока. На Linux общие скрипты ищут `/opt/curl/8`; если отдельной установки нет,
используют системные заголовки и `-lcurl`. Урок HTTP/3 по-прежнему требует
минимум libcurl 7.88 и сборку с QUIC: старый системный пакет этому не соответствует.

Переменная `CURL_PREFIX` выбирает другой комплект. Значение `system` явно выбирает
системную библиотеку. Примеры из корня репозитория:

```bash
bash scripts/build-linux.sh bonus/networking/lesson-23-http-versions/main.cpp
./build/bonus/networking/lesson-23-http-versions/main --features
CURL_PREFIX=/opt/curl/8.23.0 bash scripts/build-linux.sh bonus/networking/lesson-23-http-versions/main.cpp
CURL_PREFIX=system bash scripts/build-linux.sh bonus/networking/lesson-06-http-get/client.cpp
bash scripts/generate-compile-commands.sh
```

Скрипты разрешают ссылку на выпуск перед выбором заголовков, каталога линкера
и `rpath`. Эти же заголовки входят в базу IntelliSense. Выбор `CURL_PREFIX`
независим от `CXX`/`CXX_MODERN`; компилятор и библиотека выбираются отдельно.
Проект по умолчанию использует ветку `8`, а не `current`.

Пример [HTTP/2 и HTTP/3](lesson-23-http-versions/README.md) с `--features`
должен показать `libcurl 8.23.0; HTTP2=1; HTTP3=1` и завершиться с `0`.
Для реальных обменов подготовьте [Python-окружение и локальные службы](tests/README.md#зависимости-python)
и выполните расширенную проверку из [инструкции тестов](tests/README.md).
Проверка сертификатов остаётся включённой.

После смены `CURL_PREFIX` или ссылки ветки пересоберите программы и обновите
IntelliSense тем же выбором. Каталог прежнего выпуска сохраняйте, пока его
библиотеки нужны готовым программам. Простое перемещение установки не исправляет
абсолютные пути внутри библиотек, `pkg-config`, `curl-config` и OpenSSL;
окончательное размещение выбирайте перед сборкой.

Для отмены перенастройте проекты на системную или другую подходящую libcurl,
пересоберите программы и только затем удаляйте ссылки и выбранный каталог
выпуска. Системные curl/OpenSSL восстанавливать не требуется. Исходники,
сборка и `TMPDIR` удаляются отдельно.

## Источники

- [curl: сборка HTTP/3 с ngtcp2 и OpenSSL](https://curl.se/docs/http3.html).
- [curl: установка из исходников](https://curl.se/docs/install.html).
- [Скрипты сборки и выбор зависимостей](../../scripts/README.md).
