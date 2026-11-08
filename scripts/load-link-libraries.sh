#!/usr/bin/env bash

load_curl_options() {
    local selected=${CURL_PREFIX:-/opt/curl/8} prefix candidate library=''
    if [[ $selected == system ]]; then
        return 0
    fi
    if [[ -z ${CURL_PREFIX:-} && ! -e $selected && ! -L $selected ]]; then
        # Machines without a separate SDK keep the system development package.
        return 0
    fi
    if [[ ! -r $selected/include/curl/curl.h ]]; then
        printf 'libcurl headers not found in %s. Set CURL_PREFIX to a complete SDK or system.\n' "$selected" >&2
        return 2
    fi
    prefix=$(realpath -e -- "$selected")
    for candidate in lib lib64; do
        if [[ -f $prefix/$candidate/libcurl.so ]]; then
            library=$(realpath -e -- "$prefix/$candidate/libcurl.so")
            break
        fi
    done
    if [[ -z $library ]]; then
        printf 'libcurl.so not found in %s/lib or lib64. Install the SDK development files.\n' "$prefix" >&2
        return 2
    fi
    library_options+=(-isystem "$prefix/include")
    # Resolve the version link once so headers, linking and runtime use one release.
    local library_dir
    library_dir=$(dirname -- "$library")
    link_libraries+=("-L$library_dir" "-Wl,-rpath,$library_dir")
}

# Sourced by the build scripts. No eval: only explicitly supported library names.
load_link_libraries() {
    local library_dir=$1 library_platform=$2 library=''
    library_options=()
    link_libraries=()
    if [[ ! -f $library_dir/link-libraries.txt ]]; then
        return 0
    fi
    while IFS= read -r library || [[ -n $library ]]; do
        library=${library%$'\r'}
        case $library in
            ''|'#'*) ;;
            ws2_32|mswsock)
                if [[ $library_platform == windows ]]; then
                    link_libraries+=("-l$library")
                fi
                ;;
            curl)
                if [[ $library_platform == linux ]]; then
                    load_curl_options || return $?
                fi
                link_libraries+=(-lcurl)
                ;;
            ssl|crypto) link_libraries+=("-l$library") ;;
            pq) link_libraries+=(-lpq) ;;
            stdc++exp) link_libraries+=(-lstdc++exp) ;;
            parallel-backend)
                # libstdc++ selects TBB when its headers are visible; otherwise it
                # can use a serial backend. Ask the compiler used by this lesson.
                local query_compiler macros
                query_compiler=$(select_lesson_compiler "$library_platform")
                macros=$("$query_compiler" -std=c++17 -dM -E -x c++ - <<< '#include <execution>') || return $?
                if [[ $macros == *'#define _PSTL_PAR_BACKEND_TBB'* ]]; then
                    link_libraries+=(-ltbb)
                fi
                ;;
            *) printf 'Unsupported link library: %s\n' "$library" >&2; return 2 ;;
        esac
    done < "$library_dir/link-libraries.txt"
}
