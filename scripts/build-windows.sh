#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 || $1 != *.cpp || ! -f $1 ]]; then
    printf 'Open a C++ source file (.cpp) before building.\n' >&2
    exit 2
fi

# MSYS2 converts these paths for the native MinGW compiler when it is launched.
source_file=$(/usr/bin/realpath -- "$(/usr/bin/cygpath -u -- "$1")")
source_dir=$(/usr/bin/dirname -- "$source_file")
script_file=$(/usr/bin/cygpath -u -- "${BASH_SOURCE[0]}")
repo_dir=$(cd -- "$(/usr/bin/dirname -- "$script_file")/.." && pwd)
if [[ $source_file != "$repo_dir/"* ]]; then
    printf 'The source file must be inside this repository.\n' >&2
    exit 2
fi
relative_source=${source_file#"$repo_dir/"}
source "$repo_dir/scripts/load-compiler.sh"
load_language_settings
compiler=$(select_lesson_compiler windows)
check_lesson_compiler
output="$repo_dir/build/${relative_source%.cpp}.exe"
/usr/bin/mkdir -p -- "$(/usr/bin/dirname -- "$output")"
sources=("$source_file")
includes=()
source "$repo_dir/scripts/load-link-libraries.sh"
load_link_libraries "$source_dir" windows

if [[ $source_dir == */src && -f $source_dir/main.cpp && -d $source_dir/../include ]]; then
    sources=("$source_dir"/*.cpp)
    includes=(-I "$source_dir/../include")
else
    for companion in SimpleTimer.cpp String.cpp; do
        if [[ -f $source_dir/$companion && $source_file != "$source_dir/$companion" ]]; then
            sources+=("$source_dir/$companion")
        fi
    done
fi

exec "$compiler" "-std=$standard" "${language_options[@]}" -fdiagnostics-color=always -O0 -g \
    -Wall -Wextra -Wpedantic -pthread "${includes[@]}" "${sources[@]}" -o "$output" "${link_libraries[@]}"
