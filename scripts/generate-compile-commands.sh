#!/usr/bin/env bash
set -euo pipefail

repo_dir=$(cd -- "$(/usr/bin/dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
case $(/usr/bin/uname -s) in
    MINGW*|MSYS*|CYGWIN*) platform=windows; compiler=C:/msys64/mingw64/bin/g++.exe ;;
    Linux*) platform=linux; compiler=/usr/bin/g++ ;;
    *) printf 'Supported platforms: Linux and Windows/MSYS2.\n' >&2; exit 2 ;;
esac
native_repo=$repo_dir
if [[ $platform == windows ]]; then
    native_repo=$(/usr/bin/cygpath -m -- "$repo_dir")
fi

load_compiler_options() {
    local standard=c++17
    if [[ -f $source_dir/cxx-standard.txt ]]; then
        standard=$(<"$source_dir/cxx-standard.txt")
        standard=${standard//$'\r'/}
        case $standard in
            c++17|c++20) ;;
            *) printf 'Unsupported C++ standard: %s\n' "$standard" >&2; return 2 ;;
        esac
    fi
    compiler_options=("-std=$standard" -fdiagnostics-color=always -O0 -g
        -Wall -Wextra -Wpedantic -pthread)
    includes=()
    if [[ $source_dir == */src && -f $source_dir/main.cpp && -d $source_dir/../include ]]; then
        includes=(-I "$source_dir/../include")
    fi
}

json_string() {
    local value=$1
    value=${value//\\/\\\\}
    value=${value//\"/\\\"}
    value=${value//$'\n'/\\n}
    value=${value//$'\r'/\\r}
    value=${value//$'\t'/\\t}
    printf '"%s"' "$value"
}

native_path() {
    # All database paths belong to this repository; convert its prefix once.
    printf '%s%s' "$native_repo" "${1#"$repo_dir"}"
}

/usr/bin/mkdir -p -- "$repo_dir/build"
output="$repo_dir/build/compile_commands.json"
temporary=$(/usr/bin/mktemp "$output.XXXXXX")
trap '/usr/bin/rm -f -- "$temporary"' EXIT
first=true
{
    printf '[\n'
    # Only source trees: generated files and unrelated checkouts stay out.
    while IFS= read -r -d '' source_file; do
        source_dir=$(/usr/bin/dirname -- "$source_file")
        load_compiler_options
        if $first; then first=false; else printf ',\n'; fi
        printf '  {"directory": '
        json_string "$(native_path "$source_dir")"
        printf ', "file": '
        json_string "$(native_path "$source_file")"
        printf ', "arguments": ['
        json_string "$compiler"
        for option in "${compiler_options[@]}"; do
            printf ', '; json_string "$option"
        done
        if [[ ${#includes[@]} -gt 0 ]]; then
            printf ', "-I", '; json_string "$(native_path "${includes[1]}")"
        fi
        printf ', "-c", '; json_string "$(native_path "$source_file")"
        printf ']}'
    done < <(/usr/bin/find "$repo_dir/basics" "$repo_dir/oop" "$repo_dir/stl" \
        "$repo_dir/multithreading" "$repo_dir/examples" "$repo_dir/_template" \
        -type f -name '*.cpp' -print0 | /usr/bin/sort -z)
    printf '\n]\n'
} > "$temporary"
if [[ -f $output ]] && /usr/bin/cmp -s -- "$temporary" "$output"; then
    : # Preserve the timestamp so IntelliSense does not reload unchanged data.
else
    /usr/bin/mv -f -- "$temporary" "$output"
fi
printf 'IntelliSense database: %s (%s)\n' "$output" "$platform"
