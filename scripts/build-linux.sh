#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 || $1 != *.cpp || ! -f $1 ]]; then
    printf 'Open a C++ source file (.cpp) before building.\n' >&2
    exit 2
fi

source_file=$(realpath -- "$1")
source_dir=$(dirname -- "$source_file")
repo_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
if [[ $source_file != "$repo_dir/"* ]]; then
    printf 'The source file must be inside this repository.\n' >&2
    exit 2
fi
relative_source=${source_file#"$repo_dir/"}
source "$repo_dir/scripts/load-compiler.sh"
load_language_settings
compiler=$(select_lesson_compiler linux)
check_lesson_compiler
runtime_options=()
# A private GCC installation needs its matching shared library at runtime.
library_file=$("$compiler" -print-file-name=libstdc++.so.6)
if [[ $library_file == /* && -f $library_file ]]; then
    runtime_options=("-Wl,-rpath,$(dirname -- "$library_file")")
fi
output="$repo_dir/build/${relative_source%.cpp}"
mkdir -p -- "$(dirname -- "$output")"
sources=("$source_file")
includes=()
source "$repo_dir/scripts/load-link-libraries.sh"
load_link_libraries "$source_dir" linux

# Lessons 139 and 140 keep their sources and headers in separate directories.
if [[ $source_dir == */src && -f $source_dir/main.cpp && -d $source_dir/../include ]]; then
    sources=("$source_dir"/*.cpp)
    includes=(-I "$source_dir/../include")
else
    # Other main*.cpp files are independent programs, not extra source files.
    for companion in SimpleTimer.cpp String.cpp; do
        if [[ -f $source_dir/$companion && $source_file != "$source_dir/$companion" ]]; then
            sources+=("$source_dir/$companion")
        fi
    done
fi

exec "$compiler" "-std=$standard" "${language_options[@]}" -fdiagnostics-color=always -O0 -g \
    -Wall -Wextra -Wpedantic -pthread "${includes[@]}" "${sources[@]}" -o "$output" "${link_libraries[@]}" "${runtime_options[@]}"
