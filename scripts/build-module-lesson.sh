#!/usr/bin/env bash
# Sourced by the ordinary build entry points after compiler/library selection.

build_module_lesson() {
    local module_work unit index=0
    # PowerShell can launch MSYS2 Bash without /usr/bin on PATH.
    module_work="$(/usr/bin/dirname -- "$output")/module-build"
    /usr/bin/mkdir -p -- "$module_work"
    cd -- "$module_work"
    # This helper performs a full lesson rebuild; incompatible CMIs never survive.
    /usr/bin/rm -rf -- "$module_work/gcm.cache"
    local objects=() common_options=("-std=$standard" "${language_options[@]}"
        -fdiagnostics-color=always -O0 -g -Wall -Wextra -Wpedantic -pthread)
    local header header_count=0 standard_module=''
    if [[ -f $source_dir/header-units.txt ]]; then
        while IFS= read -r header || [[ -n $header ]]; do
            header=${header%$'\r'}
            case $header in ''|'#'*) continue ;; esac
            if [[ ! $header =~ ^[a-zA-Z0-9_-][a-zA-Z0-9_.-]*\.(h|hpp)$ || ! -f $source_dir/$header ]]; then
                printf 'Invalid header unit: %s\n' "$header" >&2
                return 2
            fi
            "$compiler" "${common_options[@]}" -x c++-header -c "$source_dir/$header" || return $?
            header_count=$((header_count + 1))
        done < "$source_dir/header-units.txt"
    fi
    if [[ -f $source_dir/standard-module.txt ]]; then
        standard_module=$(<"$source_dir/standard-module.txt")
        standard_module=${standard_module//$'\r'/}
        if [[ $standard_module != std ]]; then
            printf 'Unsupported standard module: %s\n' "$standard_module" >&2
            return 2
        fi
    fi
    while IFS= read -r unit || [[ -n $unit ]]; do
        unit=${unit%$'\r'}
        case $unit in ''|'#'*) continue ;; esac
        # Only local source filenames, with no shell interpretation or traversal.
        if [[ ! $unit =~ ^[a-zA-Z0-9_-][a-zA-Z0-9_.-]*\.(cppm|cpp)$ || ! -f $source_dir/$unit ]]; then
            printf 'Invalid module unit: %s\n' "$unit" >&2
            return 2
        fi
        index=$((index + 1))
        objects+=("$module_work/unit-$index.o")
        "$compiler" "${common_options[@]}" "${library_options[@]}" -x c++ \
            -c "$source_dir/$unit" -o "${objects[${#objects[@]}-1]}" || return $?
    done < "$source_dir/module-units.txt"
    if (( index == 0 && header_count == 0 )) && [[ -z $standard_module ]]; then
        printf 'The module lesson has no interface or implementation units.\n' >&2
        return 2
    fi
    if [[ $standard_module == std ]]; then common_options+=(--compile-std-module); fi
    # The CMI cache and objects are private to the lesson's build directory.
    exec "$compiler" "${common_options[@]}" "${library_options[@]}" "$source_file" \
        "${objects[@]}" -o "$output" "${link_libraries[@]}" "${runtime_options[@]}"
}
