#!/bin/sh
set -eu

NAME="distrotree"
PREFIX="${PREFIX:-/usr/local}"
TARGET="$PREFIX/bin/$NAME"

run_root() {
    if [ "$(id -u)" -eq 0 ]; then
        "$@"
    elif command -v doas >/dev/null 2>&1; then
        doas "$@"
    elif command -v sudo >/dev/null 2>&1; then
        sudo "$@"
    else
        printf 'error: root access is required to remove %s\n' "$TARGET" >&2
        exit 1
    fi
}

if [ ! -e "$TARGET" ]; then
    printf '%s is not installed at %s\n' "$NAME" "$TARGET"
    exit 0
fi

if [ -w "$(dirname "$TARGET")" ]; then
    rm -f "$TARGET"
else
    run_root rm -f "$TARGET"
fi

printf 'Done. %s has been removed.\n' "$NAME"
