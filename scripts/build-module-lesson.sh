#!/usr/bin/env bash
# Sourced by the ordinary build entry points after compiler/library selection.

build_module_lesson() {
    local module_work unit index=0
    module_work="$(dirname -- "$output")/module-build"
    mkdir -p -- "$module_work"
    cd -- "$module_work"
    local objects=() common_options=("-std=$standard" "${language_options[@]}"
        -fdiagnostics-color=always -O0 -g -Wall -Wextra -Wpedantic -pthread)
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
    if (( index == 0 )); then
        printf 'The module lesson has no interface or implementation units.\n' >&2
        return 2
    fi
    # The CMI cache and objects are private to the lesson's build directory.
    exec "$compiler" "${common_options[@]}" "${library_options[@]}" "$source_file" \
        "${objects[@]}" -o "$output" "${link_libraries[@]}" "${runtime_options[@]}"
}
