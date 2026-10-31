#!/usr/bin/env bash
# Shared language and compiler selection for builds and IntelliSense.

load_language_settings() {
    standard=c++17
    minimum_gcc=0
    language_options=()
    if [[ -f $source_dir/cxx-standard.txt ]]; then
        standard=$(<"$source_dir/cxx-standard.txt")
        standard=${standard//$'\r'/}
    fi
    case $standard in
        c++17|c++20|c++23) ;;
        c++26) minimum_gcc=16; language_options+=(-freflection) ;;
        *) printf 'Unsupported C++ standard: %s\n' "$standard" >&2; return 2 ;;
    esac
    if [[ -f $source_dir/gcc-min-version.txt ]]; then
        local requested
        requested=$(<"$source_dir/gcc-min-version.txt")
        requested=${requested//$'\r'/}
        if [[ ! $requested =~ ^[0-9]+$ ]]; then
            printf 'Invalid GCC minimum version: %s\n' "$requested" >&2
            return 2
        fi
        if (( requested > minimum_gcc )); then minimum_gcc=$requested; fi
    fi
    if [[ -f $source_dir/include-library.txt ]]; then
        local dependency
        dependency=$(<"$source_dir/include-library.txt")
        dependency=${dependency//$'\r'/}
        case $dependency in
            nlohmann-json)
                # An optional local download is ignored by Git; system headers also work.
                if [[ -f $repo_dir/build/dependencies/include/nlohmann/json.hpp ]]; then
                    language_options+=(-isystem "${native_repo:-$repo_dir}/build/dependencies/include")
                fi ;;
            *) printf 'Unsupported header library: %s\n' "$dependency" >&2; return 2 ;;
        esac
    fi
}

select_lesson_compiler() {
    local target_platform=$1 default_compiler modern_compiler
    if [[ $target_platform == windows ]]; then
        default_compiler=C:/msys64/mingw64/bin/g++.exe
        modern_compiler=$default_compiler
    else
        default_compiler=/usr/bin/g++
        modern_compiler=/opt/gcc-16/bin/g++
    fi
    if (( minimum_gcc >= 13 )); then
        printf '%s' "${CXX_MODERN:-${CXX:-$modern_compiler}}"
    else
        printf '%s' "${CXX:-$default_compiler}"
    fi
}

check_lesson_compiler() {
    if ! command -v "$compiler" >/dev/null 2>&1; then
        printf 'Compiler not found: %s. Set CXX_MODERN for modern lessons or CXX for ordinary lessons.\n' "$compiler" >&2
        return 2
    fi
    if (( minimum_gcc > 0 )); then
        local version
        version=$("$compiler" -dumpversion)
        version=${version%%.*}
        if [[ ! $version =~ ^[0-9]+$ ]] || (( version < minimum_gcc )); then
            printf 'This lesson requires GCC %s or newer; selected: %s (version %s).\n' "$minimum_gcc" "$compiler" "$version" >&2
            return 2
        fi
    fi
}
