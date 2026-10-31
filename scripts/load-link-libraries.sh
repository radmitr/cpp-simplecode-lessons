#!/usr/bin/env bash

# Sourced by the build scripts. No eval: only explicitly supported library names.
load_link_libraries() {
    local library_dir=$1 library_platform=$2 library=''
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
            curl) link_libraries+=(-lcurl) ;;
            *) printf 'Unsupported link library: %s\n' "$library" >&2; return 2 ;;
        esac
    done < "$library_dir/link-libraries.txt"
}
