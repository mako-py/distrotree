distrotree

An interactive terminal-based family tree of Linux distributions and Unix-like operating systems, written in C using ncurses.

Explore operating-system history, follow distribution ancestry, and inspect individual systems.

Features

- Interactive family tree with coloured branches
- Historical descriptions and release years
- Keyboard and mouse controls
- Fold and unfold branches
- Search for operating systems
- Multiple zoom levels
- Plain-text tree output

Dependencies

Build requirements:

- C compiler ("cc")
- "pkg-config"
- ncurses wide-character development files ("ncursesw")

Optional:

- "make", if using the Makefile

Install dependencies:

Distribution| Packages
Debian / Ubuntu| "build-essential libncurses-dev pkg-config"
Arch| "base-devel ncurses pkgconf"
Gentoo| "sys-devel/gcc sys-libs/ncurses dev-util/pkgconf"
Fedora| "gcc ncurses-devel pkgconf-pkg-config"
openSUSE| "gcc ncurses-devel pkg-config"
Void| "base-devel ncurses-devel pkg-config"
Alpine| "build-base ncurses-dev pkgconf"

Installation

Using the installer:

git clone https://github.com/mako-py/distrotree.git
cd distrotree
./install.sh

The installer checks dependencies, compiles the program and installs it to "/usr/local/bin".

To install without root:

PREFIX="$HOME/.local" ./install.sh

Usage

Start the interface:

distrotree

Command-line flags

Flag| Description
"-h", "--help"| Display help
"--dump [0-4]"| Print the tree without opening the interface
"--no-color"| Disable colours
"--random"| Select a random system
"--branch NAME"| Display a system and its descendants
"--search NAME"| Find and select a system
"--full-fold"| Start with all branches folded
"--full-unfold"| Start with all branches unfolded

Searches are case-insensitive and accept partial names.

Examples:

distrotree --search gentoo
distrotree --branch debian
distrotree --branch linux --search arch
distrotree --random
distrotree --dump 3
distrotree --no-color

"--random" and "--search" cannot be used together.

Keyboard controls

Key| Action
Arrow keys| Move around the tree
"h" "j" "k" "l"| Vim-style movement
"H" "J" "K" "L"| Faster movement
Shift + arrow keys| Faster movement
Page Up / Page Down| Scroll vertically
"+" / "="| Zoom in
"-" / "_"| Zoom out
Enter / Space| Fold or unfold selected branch
"c"| Fold all branches
"a"| Unfold all branches
"0" / Home| Reset the view
"q"| Quit

Mouse controls

Input| Action
Hover| Select a system and show its description
Left-click| Select and fold or unfold a branch
Scroll wheel| Move vertically
Shift + scroll| Move horizontally
Ctrl + scroll| Zoom

Mouse support depends on your terminal emulator.

Building manually

make

Or compile directly:

cc -O2 -Wall $(pkg-config --cflags ncursesw) \
    -o distrotree src/distrotree.c \
    $(pkg-config --libs ncursesw)

Install manually:

doas make install

Remove the build output:

make clean

Project structure

distrotree/
├── src/
│   └── distrotree.c
├── LICENSE
├── Makefile
├── README.md
├── install.sh
└── uninstall.sh

The operating-system data is stored in "src/distrotree.c". Entries contain a system name, year, description and depth, which determines their position in the family tree.

Uninstallation

From the repository directory:

./uninstall.sh

For a custom installation prefix:

PREFIX="$HOME/.local" ./uninstall.sh

License

MIT License.