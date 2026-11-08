#!/usr/bin/env bash
set -euo pipefail
umask 077
export PATH=/usr/bin:$PATH
script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
repo_dir=$(cd -- "$script_dir/../../../.." && pwd)
lab_dir=${PGLESSONS_HOME:-"$repo_dir/.local/postgresql"}
port=${PGLESSONS_PORT:-55432}
case $(uname -s) in
    MINGW*|MSYS*|CYGWIN*) windows=true; default_bin=/mingw64/bin; export PATH=/mingw64/bin:$PATH ;;
    Linux*) windows=false; default_bin=${PG_BIN:-$(pg_config --bindir)} ;;
    *) printf 'Supported platforms: Windows/MSYS2 and Linux.\n' >&2; exit 2 ;;
esac
native_path() { if $windows; then cygpath -m -- "$1"; else printf '%s\n' "$1"; fi; }
pg_bin=${PG_BIN:-$default_bin}
# lab.sh проверяет маркер, порт и готовность именно нашего кластера.
/usr/bin/bash "$script_dir/lab.sh" status >/dev/null
export PGHOST=127.0.0.1 PGPORT=$port PGUSER=cpp_student PGCONNECT_TIMEOUT=3
export PGPASSFILE
PGPASSFILE=$(native_path "$lab_dir/pgpass.conf")
unset PGSERVICE PGSERVICEFILE PGPASSWORD PGOPTIONS
archive=$lab_dir/backups/notes.dump
mkdir -p -- "$(dirname -- "$archive")"
"$pg_bin/pg_dump" -w -d cpp_lessons --format=custom --schema=backup_demo \
    --file="$(native_path "$archive")"
# Новая база на каждый запуск: существующие базы не удаляются и не очищаются.
restored="cpp_restore_$(date +%s)_$$"
"$pg_bin/createdb" -w --template=template0 "$restored"
"$pg_bin/pg_restore" -w --exit-on-error --single-transaction --no-owner --no-privileges \
    --dbname="$restored" "$(native_path "$archive")"
query="SELECT id::text || ':' || title FROM backup_demo.notes ORDER BY id"
original=$("$pg_bin/psql" -X -w -v ON_ERROR_STOP=1 -d cpp_lessons -Atqc "$query")
copy=$("$pg_bin/psql" -X -w -v ON_ERROR_STOP=1 -d "$restored" -Atqc "$query")
[[ -n $original && $original == "$copy" ]] || {
    printf 'Restored data differs from source.\n' >&2; exit 1
}
printf 'Backup verified: %s\nRestored database: %s\n%s\n' "$archive" "$restored" "$copy"
