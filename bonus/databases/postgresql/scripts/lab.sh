#!/usr/bin/env bash
set -euo pipefail
umask 077
export PATH=/usr/bin:$PATH

repo_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../../../.." && pwd)
lab_dir=${PGLESSONS_HOME:-"$repo_dir/.local/postgresql"}
port=${PGLESSONS_PORT:-55432}
[[ $port =~ ^[0-9]+$ && $port -ge 1024 && $port -le 65535 ]] || {
    printf 'PGLESSONS_PORT must be between 1024 and 65535.\n' >&2; exit 2;
}
case $(uname -s) in
    MINGW*|MSYS*|CYGWIN*) windows=true; default_bin=/mingw64/bin; export PATH=/mingw64/bin:$PATH ;;
    Linux*) windows=false; default_bin=${PG_BIN:-$(pg_config --bindir)} ;;
    *) printf 'Supported platforms: Windows/MSYS2 and Linux.\n' >&2; exit 2 ;;
esac
pg_bin=${PG_BIN:-$default_bin}
native_path() { if $windows; then cygpath -m -- "$1"; else printf '%s\n' "$1"; fi; }
for program in initdb pg_ctl psql createdb pg_dump pg_restore; do
    [[ -x $pg_bin/$program || -x $pg_bin/$program.exe ]] || {
        printf 'Missing %s in %s. Install PostgreSQL server or set PG_BIN.\n' "$program" "$pg_bin" >&2
        exit 2
    }
done
export PGHOST=127.0.0.1 PGPORT=$port PGUSER=cpp_student
export PGPASSFILE
PGPASSFILE=$(native_path "$lab_dir/pgpass.conf")
export PGDATABASE=cpp_lessons PGCONNECT_TIMEOUT=3
# Не подхватываем настройки постороннего сервиса/пароль из окружения.
unset PGSERVICE PGSERVICEFILE PGPASSWORD PGOPTIONS
data_dir=$lab_dir/data
marker='cpp-simplecode-postgresql-lab-v1'

check_lab() {
    [[ -f $lab_dir/lab-marker && $(<"$lab_dir/lab-marker") == "$marker" &&
       -f $data_dir/PG_VERSION && -f $lab_dir/pgpass.conf ]] || {
        printf 'Initialize this dedicated lab first: bash %s init\n' "${BASH_SOURCE[0]}" >&2
        exit 2
    }
    [[ $(<"$lab_dir/port.txt") == "$port" ]] || {
        printf 'Port differs from initialized lab; set PGLESSONS_PORT to port.txt.\n' >&2; exit 2;
    }
}

case ${1:-help} in
    init)
        if [[ -f $data_dir/PG_VERSION ]]; then
            check_lab
            printf 'Lab is already initialized: %s\n' "$lab_dir"
            exit 0
        fi
        # Не используем непустой чужой каталог и не перезаписываем его файлы.
        if [[ -d $lab_dir && -n $(ls -A -- "$lab_dir") ]]; then
            printf 'Refusing to initialize a nonempty directory: %s\n' "$lab_dir" >&2; exit 2
        fi
        command -v openssl >/dev/null || { printf 'Install openssl first.\n' >&2; exit 2; }
        mkdir -p -- "$lab_dir"
        password=$(openssl rand -hex 24)
        printf '%s\n' "$password" > "$lab_dir/init-password"
        trap 'rm -f -- "$lab_dir/init-password"' EXIT
        "$pg_bin/initdb" -D "$(native_path "$data_dir")" --username=cpp_student \
            --encoding=UTF8 --no-locale --auth-host=scram-sha-256 \
            --auth-local=scram-sha-256 --pwfile="$(native_path "$lab_dir/init-password")"
        printf '127.0.0.1:%s:*:cpp_student:%s\n' "$port" "$password" > "$lab_dir/pgpass.conf"
        chmod 600 "$lab_dir/pgpass.conf"
        unset password
        printf "\nlisten_addresses = '127.0.0.1'\nport = %s\nunix_socket_directories = ''\n" \
            "$port" >> "$data_dir/postgresql.conf"
        printf '%s\n' "$port" > "$lab_dir/port.txt"
        printf '%s\n' "$marker" > "$lab_dir/lab-marker"
        printf 'Initialized private lab: %s\n' "$lab_dir"
        ;;
    start)
        check_lab
        if ! "$pg_bin/pg_ctl" -D "$(native_path "$data_dir")" status >/dev/null 2>&1; then
            "$pg_bin/pg_ctl" -D "$(native_path "$data_dir")" \
                -l "$(native_path "$lab_dir/server.log")" -w start
        fi
        database_count=$("$pg_bin/psql" -X -w -d postgres -Atqc \
            "SELECT count(*) FROM pg_database WHERE datname = 'cpp_lessons'")
        if [[ $database_count == 0 ]]; then
            "$pg_bin/createdb" -w --template=template0 cpp_lessons
        fi
        printf 'Ready: 127.0.0.1:%s / cpp_lessons\n' "$port"
        ;;
    stop)
        check_lab
        if "$pg_bin/pg_ctl" -D "$(native_path "$data_dir")" status >/dev/null 2>&1; then
            "$pg_bin/pg_ctl" -D "$(native_path "$data_dir")" -m fast -w stop
        else
            printf 'Lab is already stopped.\n'
        fi
        ;;
    status)
        check_lab
        "$pg_bin/pg_ctl" -D "$(native_path "$data_dir")" status
        ;;
    psql)
        check_lab
        shift
        exec "$pg_bin/psql" -X -w -v ON_ERROR_STOP=1 "$@"
        ;;
    *)
        printf 'Usage: bash %s {init|start|stop|status|psql [psql options]}\n' "${BASH_SOURCE[0]}"
        exit 2
        ;;
esac
