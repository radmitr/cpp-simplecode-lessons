#!/usr/bin/env bash
set -euo pipefail
export PATH=/usr/bin:$PATH
repo_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../../../.." && pwd)
case $(uname -s) in
    MINGW*|MSYS*|CYGWIN*) platform=windows; suffix=.exe; export PATH=/mingw64/bin:$PATH ;;
    Linux*) platform=linux; suffix='' ;;
    *) printf 'Supported platforms: Windows/MSYS2 and Linux.\n' >&2; exit 2 ;;
esac
if [[ $# != 1 || ! $1 =~ ^[0-9][0-9]$ ]]; then
    printf 'Usage: bash %s 01 (lesson number 01..20)\n' "${BASH_SOURCE[0]}" >&2; exit 2
fi
sources=("$repo_dir"/bonus/databases/postgresql/lesson-"$1"-*/main.cpp)
[[ ${#sources[@]} == 1 && -f ${sources[0]} ]] || { printf 'Unknown lesson.\n' >&2; exit 2; }
source_file=${sources[0]}
/usr/bin/bash "$repo_dir/scripts/build-$platform.sh" "$source_file"
relative_source=${source_file#"$repo_dir/"}
exec "$repo_dir/build/${relative_source%.cpp}$suffix"
