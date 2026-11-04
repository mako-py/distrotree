.POSIX:

CC = cc
PKG_CONFIG = pkg-config
CFLAGS = -O2 -Wall
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
TARGET = distrotree
SOURCE = src/distrotree.c

NCURSES_CFLAGS = $(shell $(PKG_CONFIG) --cflags ncursesw 2>/dev/null)
NCURSES_LIBS = $(shell $(PKG_CONFIG) --libs ncursesw 2>/dev/null)

.PHONY: all clean install uninstall check-deps

all: check-deps $(TARGET)

check-deps:
	@command -v $(CC) >/dev/null 2>&1 || { echo "error: C compiler '$(CC)' not found" >&2; exit 1; }
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo "error: pkg-config not found" >&2; exit 1; }
	@$(PKG_CONFIG) --exists ncursesw || { echo "error: ncursesw development files not found" >&2; exit 1; }

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(NCURSES_CFLAGS) -o $@ $(SOURCE) $(NCURSES_LIBS)

install: all
	install -Dm755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)
