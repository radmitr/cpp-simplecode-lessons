#!/usr/bin/env bash
set -euo pipefail

if [[ $OSTYPE != linux* ]]; then
    printf 'ThreadSanitizer requires Linux/WSL for this lesson. Open the folder in VS Code WSL or use a Linux terminal.\n' >&2
    exit 2
fi
if [[ $# -gt 1 ]]; then
    printf 'Usage: bash run-tsan.sh [main.cpp|main2.cpp]\n' >&2
    exit 2
fi
source_name=${1:-main.cpp}
case $source_name in
    main.cpp|main2.cpp) ;;
    *) printf 'Choose main.cpp (fixed) or main2.cpp (intentional race).\n' >&2; exit 2 ;;
esac
compiler=${CXX:-clang++}
if ! command -v -- "$compiler" >/dev/null 2>&1; then
    printf 'Compiler not found: %s. Install Clang or select GCC with CXX=g++.\n' "$compiler" >&2
    exit 2
fi

lesson_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
repo_dir=$(cd -- "$lesson_dir/../../.." && pwd)
output="$repo_dir/build/multithreading/bonus/26-thread-sanitizer/${source_name%.cpp}-tsan"
mkdir -p -- "$(dirname -- "$output")"
"$compiler" -std=c++17 -O1 -g -fsanitize=thread -fno-omit-frame-pointer \
    -Wall -Wextra -Wpedantic -pthread "$lesson_dir/$source_name" -o "$output"

# При найденной гонке прекращаем выполнение с кодом 66.
TSAN_OPTIONS="${TSAN_OPTIONS:+$TSAN_OPTIONS:}halt_on_error=1:exitcode=66" "$output"
