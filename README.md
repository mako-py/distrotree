# distrotree

An interactive, terminal-based family tree of operating systems. Follow the relationships between Unix, Linux distributions, BSD systems, and other operating-system branches, inspect short histories, and explore the tree without leaving your terminal.

![License](https://img.shields.io/github/license/mako-py/distrotree?style=flat-square)
![Stars](https://img.shields.io/github/stars/mako-py/distrotree?style=flat-square)
![Forks](https://img.shields.io/github/forks/mako-py/distrotree?style=flat-square)
![Issues](https://img.shields.io/github/issues/mako-py/distrotree?style=flat-square)
![Last commit](https://img.shields.io/github/last-commit/mako-py/distrotree?style=flat-square)
![Top language](https://img.shields.io/github/languages/top/mako-py/distrotree?style=flat-square)
![Repo size](https://img.shields.io/github/repo-size/mako-py/distrotree?style=flat-square)

## Contents

- [What it does](#what-it-does)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Build manually](#build-manually)
- [Usage](#usage)
- [Controls](#controls)
- [Colour and terminal support](#colour-and-terminal-support)
- [Project layout](#project-layout)
- [Adding or editing systems](#adding-or-editing-systems)
- [Troubleshooting](#troubleshooting)
- [Uninstallation](#uninstallation)
- [Contributing](#contributing)
- [License](#license)

## What it does

`distrotree` displays operating systems as a connected family tree. Each entry can include its year and a short historical note. Branches can be folded and unfolded, the view can be zoomed and panned, and selecting a system opens its description in a panel at the bottom of the terminal.

The data is stored directly in the C source as a pre-order list. Each entry has an explicit depth, so the relationships are easy to read and edit.

## Features

- Interactive ncurses interface.
- Coloured branches to make families easier to follow.
- Short historical notes and release years for entries.
- Mouse support for hovering, selecting, folding, scrolling and zooming.
- Keyboard navigation, including Vim-style `h`, `j`, `k`, `l` movement.
- Semantic zoom levels that reveal more of the tree, years and spacing as you zoom in.
- Fold and unfold individual branches or the whole tree.
- Search for a system by full or partial name.
- Start directly at a chosen system or at a random system.
- Text-only tree output for terminals, logs or piping.
- `--no-color` mode.

## Requirements

### Runtime

- Linux or another Unix-like environment with a working terminal.
- A terminal that supports ncurses and preferably UTF-8.

### Build dependencies

| Dependency | Why it is needed |
|---|---|
| C compiler (`cc`) | Compiles the program. GCC and Clang should both work. |
| `pkg-config` | Locates the ncursesw compiler and linker flags. |
| ncurses wide-character development files | Provides `ncurses.h`, wide-character drawing and terminal input. |
| `make` | Optional. Only needed when using the Makefile. |

The installer checks for the compiler, `pkg-config`, and the `ncursesw` development package. If something is missing, it attempts to install the relevant packages using the detected distribution's package manager.

### Package names by distribution

| Distribution | Packages |
|---|---|
| Debian / Ubuntu | `build-essential libncurses-dev pkg-config` |
| Arch Linux | `base-devel ncurses pkgconf` |
| Gentoo | `sys-devel/gcc sys-libs/ncurses dev-util/pkgconf` |
| Fedora | `gcc ncurses-devel pkgconf-pkg-config` |
| openSUSE | `gcc ncurses-devel pkg-config` |
| Void Linux | `base-devel ncurses-devel pkg-config` |
| Alpine Linux | `build-base ncurses-dev pkgconf` |

If your distribution is not listed, install the equivalent packages manually and run the installer again.

## Installation

### Automatic installation

Clone the repository and run the installer from its root directory:

```sh
git clone https://github.com/mako-py/distrotree.git
cd distrotree
chmod +x install.sh
./install.sh
```

The installer will:

1. Check that `src/distrotree.c` exists.
2. Check for `cc`, `pkg-config`, and `ncursesw` development files.
3. Install missing build dependencies on supported distributions.
4. Compile the program with optimisation enabled and warnings turned on.
5. Install the executable to `/usr/local/bin` by default.
6. Print a completion message and the command used to launch it.

The installer uses `doas` when available, then falls back to `sudo`. If neither is available, system-wide installation requires you to run the script as root or choose a writable prefix.

### Install without root

You can install it in your home directory:

```sh
PREFIX="$HOME/.local" ./install.sh
```

Make sure `$HOME/.local/bin` is in your `PATH`.

### Choose another prefix

```sh
PREFIX="/opt/distrotree" ./install.sh
```

The executable will be placed in the prefix's `bin` directory.

## Build manually

You can compile without the installer if the dependencies are already present:

```sh
cc -O2 -Wall $(pkg-config --cflags ncursesw) \
    -o distrotree src/distrotree.c \
    $(pkg-config --libs ncursesw)
```

Or use the Makefile:

```sh
make
```

Install the result:

```sh
sudo make install
```

To use `doas` instead:

```sh
doas make install
```

To install under a different prefix:

```sh
make PREFIX="$HOME/.local" install
```

Remove the local build output with:

```sh
make clean
```

## Usage

Start the interactive interface:

```sh
distrotree
```

Show the command-line help:

```sh
distrotree --help
```

Print the tree instead of opening the interactive interface:

```sh
distrotree --dump
```

Choose a dump zoom level from `0` to `4`:

```sh
distrotree --dump 4
```

Disable colours:

```sh
distrotree --no-color
```

Start with every branch folded or unfolded:

```sh
distrotree --full-fold
distrotree --full-unfold
```

Find and select a system. Matching is case-insensitive and partial names are accepted:

```sh
distrotree --search gentoo
distrotree --search "linux mint"
```

Show only one system and its descendants:

```sh
distrotree --branch debian
distrotree --branch bsd
```

Pick a random system:

```sh
distrotree --random
```

Combine a branch restriction with search or random selection:

```sh
distrotree --branch linux --search gentoo
distrotree --branch bsd --random
```

`--random` and `--search` cannot be used together.

## Controls

### Keyboard

| Key | Action |
|---|---|
| `↑` / `↓` / `←` / `→` | Pan around the tree. |
| `h` / `j` / `k` / `l` | Pan left, down, up and right. |
| `Shift` + arrow keys | Pan faster. |
| `H` / `J` / `K` / `L` | Pan faster using Vim-style keys. |
| `Page Up` / `Page Down` | Pan vertically faster. |
| `+` / `=` | Zoom in. |
| `-` / `_` | Zoom out. |
| `Enter` / `Space` | Fold or unfold the selected branch. |
| `c` | Collapse to an overview. |
| `a` | Expand all branches. |
| `0` / `Home` | Reset the view. |
| `q` | Quit. |

When mouse reporting is unavailable, the system nearest the centre of the visible tree is selected.

### Mouse

| Input | Action |
|---|---|
| Hover over a system | Show its description in the bottom panel. |
| Left-click a system | Select and fold or unfold its branch. |
| Mouse wheel | Scroll vertically. |
| `Shift` + mouse wheel | Scroll horizontally. |
| `Ctrl` + mouse wheel | Zoom around the pointer. |

Mouse reporting depends on the terminal emulator and its configuration. Keyboard controls remain available without a mouse.

## Colour and terminal support

Branches use a palette of distinct colours. The palette uses 256-colour values when the terminal reports at least 256 colours, and falls back to the standard terminal palette otherwise. `--no-color` disables colour output.

The interface uses ncurses wide-character functions for Unicode box-drawing characters. If UTF-8 is unavailable, it falls back to the terminal's alternate character set where possible.

For the best result, use a UTF-8 terminal with colour support and a reasonably wide window. The program adapts to terminal resizing.

## Project layout

```text
distrotree/
├── src/
│   └── distrotree.c   # program source and operating-system data
├── .gitignore
├── LICENSE
├── Makefile           # manual build and install targets
├── README.md
├── install.sh         # dependency check, build and installation
└── uninstall.sh       # removes the installed executable
```

## Adding or editing systems

The operating-system data is stored in `src/distrotree.c` in the `defs[]` array.

Each entry has this shape:

```c
T(depth, "System name", year, "Short description"),
```

The depth controls the parent relationship:

- A depth-`0` entry starts a separate tree.
- An entry one level deeper than the previous parent becomes its child.
- Put children directly after their parent, in pre-order.

There are three entry macros:

| Macro | Meaning |
|---|---|
| `T(...)` | Normal entry. |
| `S(...)` | Stub entry, displayed dimly and excluded from normal family colouring. |
| `K(...)` | Trunk entry. Its children start new colour families. |

When adding an entry, keep the list in pre-order and check that its depth reflects the relationship you intend. Keep descriptions short enough to fit the detail panel, and include a year when a useful founding or first-release year is known.

After editing, rebuild and check the output:

```sh
make clean
make
./distrotree --dump 3
./distrotree --help
```

Historical relationships can be debatable, especially for systems that share ancestry or have changed bases over time. If you correct an entry, a short source or explanation in the pull request is helpful.

## Troubleshooting

### `pkg-config` cannot find `ncursesw`

Install the ncurses development package for your distribution. Make sure its wide-character `pkg-config` metadata is installed, then check:

```sh
pkg-config --modversion ncursesw
```

### `ncurses.h: No such file or directory`

The ncurses development headers are missing. Install the appropriate development package, not just the runtime ncurses library.

### `cc: command not found`

Install GCC or Clang and ensure a `cc` command is available. On some systems, installing the compiler package does not create the `cc` alternative automatically.

### The colours look different

The terminal controls the actual appearance of standard colours. A terminal theme can change how those colours look. Try another terminal palette or use `--no-color` if needed.

### Mouse input does not work

Mouse reporting varies by terminal emulator. Try enabling mouse support in the terminal or use the keyboard controls.

### The tree is too large for the terminal

Use `--dump 0` for a compact text view, fold branches in the interactive interface, or restrict the view with `--branch NAME`.

## Uninstallation

If installed with the default prefix:

```sh
./uninstall.sh
```

For a custom prefix, use the same prefix used during installation:

```sh
PREFIX="$HOME/.local" ./uninstall.sh
```

You can also remove the executable manually:

```sh
rm -f /usr/local/bin/distrotree
```

## Contributing

Bug reports, corrections to the operating-system history, and improvements to the interface are welcome. When reporting a bug, include:

- Your distribution and version.
- Your terminal emulator and `$TERM` value.
- Whether you use a UTF-8 locale.
- The exact command you ran.
- The compiler output, if the issue happened during compilation.

For changes to the tree data, explain the historical relationship being changed. Keep changes focused and avoid adding unrelated dependencies.

## License

`distrotree` is released under the MIT License. See [LICENSE](LICENSE) for the full text.
