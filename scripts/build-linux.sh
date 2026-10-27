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
output="$repo_dir/build/${relative_source%.cpp}"
mkdir -p -- "$(dirname -- "$output")"
sources=("$source_file")
includes=()

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

exec /usr/bin/g++ -std=c++17 -fdiagnostics-color=always -O0 -g \
    -Wall -Wextra -Wpedantic -pthread "${includes[@]}" "${sources[@]}" -o "$output"
