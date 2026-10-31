#!/usr/bin/env bash
set -euo pipefail
source_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
repo_dir=$(cd -- "$source_dir/../../.." && pwd)
case $(uname -s) in Linux*) ;; *) printf 'Run this check on Linux/WSL with ASan installed.\n' >&2; exit 2 ;; esac
compiler=${CXX:-/usr/bin/g++}
output_dir="$repo_dir/build/basics/bonus/29-diagnostics/sanitizers"
mkdir -p -- "$output_dir"
"$compiler" -std=c++17 -x c++ -O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined \
    "$source_dir/invalid-access.txt" -o "$output_dir/invalid-access"
set +e
"$output_dir/invalid-access" >"$output_dir/output.txt" 2>"$output_dir/diagnostic.txt"
status=$?
set -e
if [[ $status -eq 0 ]] || ! grep -q 'heap-use-after-free' "$output_dir/diagnostic.txt"; then
    cat "$output_dir/diagnostic.txt" >&2
    printf 'Expected an ASan heap-use-after-free diagnosis.\n' >&2
    exit 1
fi
printf 'Expected ASan diagnostic confirmed: %s\n' "$output_dir/diagnostic.txt"
