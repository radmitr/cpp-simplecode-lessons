#!/usr/bin/env bash
set -euo pipefail
source_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
repo_dir=$(cd -- "$source_dir/../../.." && pwd)
case $(uname -s) in Linux*) ;; *) printf 'Run this check on Linux/WSL with ASan installed.\n' >&2; exit 2 ;; esac
compiler=${CXX:-/usr/bin/g++}
output_dir="$repo_dir/build/basics/additions/30-diagnostics/sanitizers"
mkdir -p -- "$output_dir"
runtime_options=()
runtime_library=$("$compiler" -print-file-name=libasan.so)
if [[ $runtime_library == /* && -f $runtime_library ]]; then
    # Pin the runtime to the installed release even when the compiler uses a symlink.
    runtime_library=$(readlink -f -- "$runtime_library")
    runtime_options=("-Wl,-rpath,$(dirname -- "$runtime_library")")
fi
"$compiler" -std=c++17 -x c++ -O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined \
    "$source_dir/invalid-access.txt" -o "$output_dir/invalid-access" "${runtime_options[@]}"
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
