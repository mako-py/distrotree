#!/bin/sh
set -eu

NAME="distrotree"
SOURCE="src/distrotree.c"
PREFIX="${PREFIX:-/usr/local}"
BINDIR="$PREFIX/bin"

info() { printf '%s\n' "$1"; }
fail() { printf 'error: %s\n' "$1" >&2; exit 1; }

[ -f "$SOURCE" ] || fail "src/distrotree.c not found. Run this script from the repository root."

run_root() {
    if [ "$(id -u)" -eq 0 ]; then
        "$@"
    elif command -v doas >/dev/null 2>&1; then
        doas "$@"
    elif command -v sudo >/dev/null 2>&1; then
        sudo "$@"
    else
        fail "root access is required. Install doas or sudo, or choose a writable PREFIX."
    fi
}

have_deps() {
    command -v cc >/dev/null 2>&1 &&
    command -v pkg-config >/dev/null 2>&1 &&
    pkg-config --exists ncursesw
}

if ! have_deps; then
    [ -r /etc/os-release ] || fail "cannot identify this distribution; install a C compiler, pkg-config and ncursesw development files manually."
    . /etc/os-release
    DISTRO="${ID:-unknown} ${ID_LIKE:-}"
    info "Installing build dependencies for ${PRETTY_NAME:-$ID}..."

    case "$DISTRO" in
        *debian*|*ubuntu*)
            run_root apt-get update
            run_root apt-get install -y build-essential libncurses-dev pkg-config
            ;;
        *arch*)
            run_root pacman -S --needed base-devel ncurses pkgconf
            ;;
        *gentoo*)
            run_root emerge --getbinpkg --ask sys-devel/gcc sys-libs/ncurses dev-util/pkgconf
            ;;
        *fedora*)
            run_root dnf install -y gcc ncurses-devel pkgconf-pkg-config
            ;;
        *opensuse*|*suse*)
            run_root zypper install -y gcc ncurses-devel pkg-config
            ;;
        *void*)
            run_root xbps-install -S base-devel ncurses-devel pkg-config
            ;;
        *alpine*)
            run_root apk add build-base ncurses-dev pkgconf
            ;;
        *)
            fail "unsupported distribution ($DISTRO). Install a C compiler, pkg-config and ncursesw development files manually, then rerun this script."
            ;;
    esac
fi

have_deps || fail "dependencies are still missing. Required: cc, pkg-config and ncursesw development files."

build_dir="$(mktemp -d)"
trap 'rm -rf "$build_dir"' EXIT HUP INT TERM
info "Compiling $NAME..."
# pkg-config emits the compiler and linker flags required by ncursesw.
# Intentional word splitting is needed to pass those flags as separate arguments.
# shellcheck disable=SC2046
cc -O2 -Wall $(pkg-config --cflags ncursesw) -o "$build_dir/$NAME" "$SOURCE" $(pkg-config --libs ncursesw) || fail "compilation failed."

info "Installing to $BINDIR..."
if [ -w "$BINDIR" ] || { [ ! -e "$BINDIR" ] && [ -w "$PREFIX" ]; }; then
    install -Dm755 "$build_dir/$NAME" "$BINDIR/$NAME"
else
    run_root install -Dm755 "$build_dir/$NAME" "$BINDIR/$NAME"
fi

printf '\nDone. %s is installed.\n' "$NAME"
printf 'Run it with: %s\n' "$NAME"
