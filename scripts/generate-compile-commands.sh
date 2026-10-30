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
    standard=c++17
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

json_escape() {
    local value=$1
    value=${value//\\/\\\\}
    value=${value//\"/\\\"}
    value=${value//$'\n'/\\n}
    value=${value//$'\r'/\\r}
    value=${value//$'\t'/\\t}
    REPLY="\"$value\""
}

json_string() {
    json_escape "$1"
    printf '%s' "$REPLY"
}

replace_if_changed() {
    local previous='' replacement=''
    if [[ -f $output ]]; then
        IFS= read -r -d '' previous < "$output" || true
    fi
    IFS= read -r -d '' replacement < "$temporary" || true
    if [[ -f $output && $previous == "$replacement" ]]; then
        # Preserve the timestamp so IntelliSense does not reload unchanged data.
        /usr/bin/rm -f -- "$temporary"
    else
        /usr/bin/mv -f -- "$temporary" "$output"
    fi
}

generate_workspace_configuration() {
    local workspace_dir=$1
    local source_dir=$workspace_dir standard
    local first_line='' checksum='' relative_workspace database_path content=''
    local previous='' body=''
    output="$workspace_dir/.vscode/c_cpp_properties.json"
    if [[ -e $output || -L $output ]]; then
        if [[ -f $output && ! -L $output ]]; then
            IFS= read -r -d '' previous < "$output" || true
            first_line=${previous%%$'\n'*}
        fi
        if [[ $first_line != "$generated_header"* ]]; then
            printf 'Keeping custom IntelliSense configuration: %s\n' "$output" >&2
            preserved_count=$((preserved_count + 1))
            return
        fi
    fi

    # Multi-file lessons keep their standard marker beside src/main.cpp.
    if [[ -f $workspace_dir/src/main.cpp && -d $workspace_dir/include ]]; then
        source_dir=$workspace_dir/src
    fi
    load_compiler_options
    relative_workspace=${workspace_dir#"$repo_dir/"}
    database_path=../build/compile_commands.json
    while [[ $relative_workspace == */* ]]; do
        database_path=../$database_path
        relative_workspace=${relative_workspace#*/}
    done
    json_escape "\${workspaceFolder}/$database_path"
    database_path=$REPLY
    IFS= read -r -d '' content <<EOF || true
{
    "configurations": [
        {
            "name": "Linux",
            "compilerPath": "/usr/bin/g++",
            "cppStandard": "$standard",
            "intelliSenseMode": "linux-gcc-x64",
            "compileCommands": [$database_path]
        },
        {
            "name": "Win32",
            "compilerPath": "C:/msys64/mingw64/bin/g++.exe",
            "cppStandard": "$standard",
            "intelliSenseMode": "windows-gcc-x64",
            "compileCommands": [$database_path]
        }
    ],
    "version": 4
}
EOF
    checksum=${configuration_checksums[$content]-}
    if [[ -z $checksum ]]; then
        checksum=$(printf '%s' "$content" | /usr/bin/sha256sum)
        checksum=${checksum%% *}
        configuration_checksums[$content]=$checksum
    fi
    local expected_checksum=$checksum
    if [[ -n $previous ]]; then
        body=${previous#*$'\n'}
        # The expected body is already known: unchanged files need no subprocesses.
        if [[ $body == "$content" && $first_line == "$generated_header$checksum" ]]; then
            configurations_count=$((configurations_count + 1))
            return
        fi
        checksum=$(printf '%s' "$body" | /usr/bin/sha256sum)
        checksum=${checksum%% *}
        if [[ $first_line != "$generated_header$checksum" ]]; then
            printf 'Keeping custom IntelliSense configuration: %s\n' "$output" >&2
            preserved_count=$((preserved_count + 1))
            return
        fi
    fi
    checksum=$expected_checksum
    temporary=$(/usr/bin/mktemp "$output.XXXXXX")
    {
        printf '%s%s\n' "$generated_header" "$checksum"
        printf '%s' "$content"
    } > "$temporary"
    replace_if_changed
    configurations_count=$((configurations_count + 1))
}

/usr/bin/mkdir -p -- "$repo_dir/build"
database="$repo_dir/build/compile_commands.json"
output=$database
temporary=$(/usr/bin/mktemp "$output.XXXXXX")
trap '/usr/bin/rm -f -- "$temporary"' EXIT
first=true
{
    printf '[\n'
    # Only source trees: generated files and unrelated checkouts stay out.
    while IFS= read -r -d '' source_file; do
        source_dir=${source_file%/*}
        load_compiler_options
        if $first; then first=false; else printf ',\n'; fi
        printf '  {"directory": '
        json_string "$native_repo${source_dir#"$repo_dir"}"
        printf ', "file": '
        json_string "$native_repo${source_file#"$repo_dir"}"
        printf ', "arguments": ['
        json_string "$compiler"
        for option in "${compiler_options[@]}"; do
            printf ', '; json_string "$option"
        done
        if [[ ${#includes[@]} -gt 0 ]]; then
            printf ', "-I", '; json_string "$native_repo${includes[1]#"$repo_dir"}"
        fi
        printf ', "-c", '; json_string "$native_repo${source_file#"$repo_dir"}"
        printf ']}'
    done < <(/usr/bin/find "$repo_dir/basics" "$repo_dir/oop" "$repo_dir/stl" \
        "$repo_dir/multithreading" "$repo_dir/examples" "$repo_dir/_template" \
        -type f -name '*.cpp' -print0 | /usr/bin/sort -z)
    printf '\n]\n'
} > "$temporary"
replace_if_changed

# A checksum distinguishes untouched generated files from user edits.
# VS Code accepts the leading comment in c_cpp_properties.json (JSON with comments).
generated_header='// Generated by scripts/generate-compile-commands.sh; sha256: '
declare -A configuration_checksums=()
configurations_count=0
preserved_count=0
while IFS= read -r -d '' task_file; do
    generate_workspace_configuration "${task_file%/.vscode/tasks.json}"
done < <(/usr/bin/find "$repo_dir/basics" "$repo_dir/oop" "$repo_dir/stl" \
    "$repo_dir/multithreading" "$repo_dir/examples" "$repo_dir/_template" \
    -type f -path '*/.vscode/tasks.json' -print0 | /usr/bin/sort -z)
printf 'IntelliSense database: %s (%s); lesson configs: %d; kept custom: %d\n' \
    "$database" "$platform" "$configurations_count" "$preserved_count"
