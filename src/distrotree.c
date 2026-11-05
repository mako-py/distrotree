#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif
#include <ctype.h>
#include <langinfo.h>
#include <locale.h>
#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

typedef struct { int depth; const char *name; int year; const char *note; int kind; } Def;
#define T(d, n, y, t) { d, n, y, t, 0 }
#define S(d, n, y, t) { d, n, y, t, 1 }
#define K(d, n, y, t) { d, n, y, t, 2 }

static const Def defs[] = {
 K(0,"Multics",1964,"Time-sharing OS from MIT, GE and Bell Labs. Bell Labs left the project in 1969; its sprawling design is why Unix ('Unics') was kept small."),
 K(1,"Unix",1969,"Written at Bell Labs by Ken Thompson and Dennis Ritchie, rewritten in C in 1973. Root of every Unix and Unix-like system."),
 K(2,"Linux",1991,"A Unix-like kernel written from scratch by Linus Torvalds (first developed on MINIX). No Unix code, but Unix by design; paired with the GNU userland (1983)."),

 T(3,"Debian",1993,"Announced by Ian Murdock in 1993. Community-run, .deb packages and apt, with stable/testing/unstable branches. The biggest family of derivatives."),
  T(4,"Ubuntu",2004,"Canonical (Mark Shuttleworth). Built from Debian unstable snapshots; a release every 6 months, an LTS every 2 years."),
   T(5,"Linux Mint",2006,"Ubuntu LTS base with Cinnamon, MATE and Xfce editions. Its Debian twin, LMDE, sits under Debian."),
   T(5,"Pop!_OS",2017,"System76's Ubuntu-based distro, home of the COSMIC desktop."),
   T(5,"elementary OS",2011,"Ubuntu LTS base with its own Pantheon desktop. The first release was called 'Jupiter'."),
   T(5,"Zorin OS",2009,"Ubuntu-based, tuned to feel familiar to Windows and macOS switchers."),
   T(5,"Kubuntu",2005,"Official Ubuntu flavour using KDE Plasma."),
   T(5,"Xubuntu",2006,"Official Ubuntu flavour using Xfce."),
   T(5,"Lubuntu",2010,"Official Ubuntu flavour (since 11.10), using LXQt since 2018 (LXDE before)."),
   T(5,"Ubuntu MATE",2015,"Official flavour (since 15.04) with the MATE desktop, a GNOME 2 fork."),
   T(5,"Ubuntu Budgie",2016,"Official flavour (since 17.04) with the Budgie desktop."),
   T(5,"Ubuntu Studio",2007,"Official flavour for audio, video and graphics production."),
   T(5,"Ubuntu Unity",2022,"The Unity 7 desktop revived by the community; an official flavour since 23.04."),
   T(5,"Ubuntu Kylin",2010,"Official Ubuntu flavour tailored for Chinese-speaking users."),
   T(5,"Edubuntu",2005,"Official Ubuntu flavour for schools, with educational apps and classroom tools."),
   T(5,"KDE neon",2016,"KDE's own showcase: Ubuntu LTS base plus the newest Plasma and KDE apps."),
   T(5,"Linux Lite",2012,"Lightweight Xfce distro on Ubuntu LTS, aimed at older PCs and Windows switchers."),
   T(5,"Bodhi Linux",2011,"Minimalist Ubuntu-based distro built around the Moksha desktop, an Enlightenment fork."),
   T(5,"Trisquel",2005,"Ubuntu-derived and built only from free software; endorsed by the FSF."),
   T(5,"Ubuntu Touch",2013,"Ubuntu for phones and tablets. Canonical dropped it in 2017 and the UBports community carries it on."),
  T(4,"Devuan",2014,"Debian fork without systemd, started over the 2014 init-system dispute. First stable release in 2017."),
  T(4,"LMDE",2010,"Linux Mint Debian Edition: Mint's desktop on Debian stable instead of Ubuntu, Mint's insurance policy."),
  T(4,"Knoppix",2000,"Klaus Knopper's Debian-based live CD; made running Linux straight from a disc mainstream."),
   T(5,"Damn Small Linux",2005,"Tiny desktop that fit in 50 MB, Knoppix-based. Revived in 2024."),
   T(5,"Kanotix",2004,"Knoppix-derived live distro that tracks Debian unstable (sid)."),
  T(4,"antiX",2007,"Light, systemd-free live distro on Debian; began as an offshoot of MEPIS."),
  T(4,"MX Linux",2014,"Joint project of the antiX and former MEPIS communities, on Debian stable."),
  T(4,"Kali Linux",2013,"Offensive Security's penetration-testing distro on Debian testing; successor to BackTrack."),
  T(4,"Parrot OS",2013,"Debian-based security and privacy distro."),
  T(4,"Tails",2009,"Amnesic live system that routes everything through Tor; Debian-based."),
  T(4,"Whonix",2012,"Two-VM design: a Tor gateway plus a workstation, so apps can only reach the net through Tor."),
  T(4,"Raspberry Pi OS",2012,"Official OS of the Raspberry Pi; began as the community port Raspbian."),
   T(5,"RetroPie",2012,"Retro-gaming OS for the Raspberry Pi, built on Raspberry Pi OS and EmulationStation."),
  T(4,"Armbian",2013,"Debian and Ubuntu images tuned for ARM single-board computers."),
  T(4,"Proxmox VE",2008,"Virtualisation platform: Debian plus KVM, LXC and a web UI."),
  T(4,"PureOS",2015,"Purism's FSF-endorsed distro for its Librem hardware; Debian-based."),
  T(4,"Deepin",2008,"Chinese distro with the Deepin Desktop Environment; Ubuntu-based early on, Debian-based since 2015."),
  T(4,"Vanilla OS",2022,"Immutable desktop with transactional updates. Ubuntu-based at first, Debian-based since 2023."),
  T(4,"SparkyLinux",2012,"Polish Debian-based distro with lightweight desktops such as LXQt, Xfce and MATE."),
  T(4,"Q4OS",2014,"Lightweight Debian-based distro with Trinity (a KDE 3 fork) and Plasma editions."),
  T(4,"CrunchBang",2008,"Corey Hanson's minimal Openbox distro, written '#!'. Discontinued in 2015."),
   T(5,"BunsenLabs",2015,"Community continuation of CrunchBang, on Debian stable."),
  T(4,"Astra Linux",2008,"Russian Debian-based distro certified for government and military use."),
  T(4,"Corel Linux",1999,"Corel's Debian-based desktop distro. Sold to Xandros in 2001."),
   T(5,"Xandros",2001,"Corel Linux's heir; the first OS on the Asus Eee PC."),
  T(4,"Linspire",2001,"Began as Lindows (Michael Robertson); renamed Linspire in 2004 after Microsoft's trademark suit."),
  T(4,"Maemo",2005,"Nokia's Debian-based mobile OS for the 770 and N900 internet tablets."),
   T(5,"MeeGo",2010,"Merger of Maemo and Intel's Moblin (RPM-based). Cancelled in 2011."),
    T(6,"Sailfish OS",2013,"Jolla's MeeGo-descended mobile OS."),
    T(6,"Tizen",2012,"Samsung and Intel's successor to MeeGo; runs smartwatches and TVs."),

 T(3,"Red Hat Linux",1995,"Red Hat's first distro; introduced RPM. Retired in 2003 and split into Fedora (community) and RHEL (commercial)."),
  T(4,"Fedora",2003,"Red Hat-sponsored community distro with 6-month releases; the upstream for RHEL."),
   T(5,"CentOS Stream",2019,"Sits between Fedora and RHEL: upcoming RHEL minor releases are developed here."),
   T(5,"Nobara",2021,"Fedora-based, gaming-focused remix by GloriousEggroll."),
   T(5,"Bazzite",2023,"Image-based Fedora Atomic spin for gaming PCs and handhelds."),
   T(5,"Asahi Linux",2022,"Fedora Asahi Remix: Linux for Apple Silicon Macs."),
   T(5,"Fedora Silverblue",2018,"Image-based immutable Fedora Workstation using rpm-ostree."),
   T(5,"Fedora CoreOS",2019,"Merger of CoreOS Container Linux and Project Atomic; an auto-updating container host."),
   T(5,"Red Star OS",2013,"North Korea's national OS. First release 2002; version 3.0 is Fedora-based with a macOS-like desktop."),
  T(4,"RHEL",2002,"Red Hat Enterprise Linux, the subscription enterprise distro. Major versions branch from Fedora; minor ones come via CentOS Stream."),
   T(5,"CentOS Linux",2004,"Free rebuild of RHEL. Replaced by CentOS Stream: CentOS 8 ended in 2021, CentOS 7 in 2024."),
   T(5,"Rocky Linux",2021,"Founded by CentOS co-founder Gregory Kurtzer after the CentOS 8 cut; a RHEL rebuild."),
   T(5,"AlmaLinux",2021,"CloudLinux's answer to the end of CentOS 8; now run by a non-profit foundation."),
   T(5,"Oracle Linux",2006,"Oracle's RHEL rebuild, with its own Unbreakable Enterprise Kernel."),
   T(5,"Scientific Linux",2004,"CERN and Fermilab's RHEL rebuild for labs; retired in 2024."),
  T(4,"Mandrake Linux",1998,"Started as Red Hat plus KDE, aimed at newcomers. Became Mandriva in 2005."),
   T(5,"Mandriva Linux",2005,"Mandrake after merging with Conectiva. Its heirs live on below."),
    T(6,"Mageia",2010,"Community fork of Mandriva Linux by ex-Mandriva staff and volunteers."),
    T(6,"OpenMandriva",2012,"Community-run continuation of Mandriva Linux."),
    T(6,"ROSA",2010,"Russian distro derived from Mandriva Linux."),
   T(5,"PCLinuxOS",2003,"Rolling release forked from Mandrake 9.2 by Texstar."),
  T(4,"Yellow Dog Linux",1999,"Red Hat-based distro for PowerPC hardware: Apple Macs and the PlayStation 3."),

 T(3,"SLS",1992,"Softlanding Linux System, an early full distribution. Slackware started as a cleaned-up SLS."),
  T(4,"Slackware",1993,"Patrick Volkerding's distro; the oldest still maintained. Simple BSD-style init and plain tarball packages."),
   T(5,"SUSE Linux",1994,"Began as a German Slackware repackaging in 1994; later adopted RPM and YaST and went its own way."),
    T(6,"SUSE Linux Enterprise",2000,"Commercial SUSE (SLES/SLED); the stable core that openSUSE Leap shares."),
    T(6,"openSUSE",2005,"Community branch opened when Novell turned SUSE Linux into a community project."),
     T(7,"Leap",2015,"openSUSE's regular releases, sharing core packages with SUSE Linux Enterprise."),
     T(7,"Tumbleweed",2010,"openSUSE's rolling release, tested with openQA."),
   T(5,"Salix",2009,"Slackware-compatible, adds dependency-aware package handling."),
   T(5,"Zenwalk",2004,"Slackware-based desktop distro; began as Minislack."),
   T(5,"Porteus",2010,"Portable, RAM-friendly live distro based on Slackware."),
   T(5,"Slax",2002,"Portable live distro. Slackware-based at first, Debian-based since 2018."),
   T(5,"Vector Linux",1999,"Light Slackware-based desktop distro."),

 T(3,"Arch Linux",2002,"Judd Vinet's rolling-release distro, inspired by CRUX. pacman, the AUR, the Arch Wiki and a KISS ethos."),
  T(4,"Manjaro",2011,"User-friendly Arch-based distro with its own repos, held back slightly for stability."),
  T(4,"Antergos",2012,"Arch-based distro with a graphical installer. Discontinued in 2019; its community went on to EndeavourOS."),
  T(4,"EndeavourOS",2019,"Community successor to Antergos; stays close to plain Arch with a friendly installer."),
  T(4,"Garuda Linux",2020,"Arch-based, performance and gaming minded, Btrfs snapshots by default."),
  T(4,"Artix Linux",2017,"Arch without systemd: OpenRC, runit, s6 or dinit."),
  T(4,"CachyOS",2021,"Arch-based with optimised package builds and custom kernel tuning."),
  T(4,"BlackArch",2013,"Arch-based penetration-testing distro with a huge toolset."),
  T(4,"ArcoLinux",2017,"Arch-based, teaching-oriented distro with video tutorials and many desktop choices."),
  T(4,"Parabola",2009,"FSF-endorsed Arch-based distro with free software only (GNU/Linux-libre kernel)."),
  T(4,"SteamOS 3",2022,"Valve's Arch-based OS for the Steam Deck. SteamOS 1 and 2 were Debian-based."),

 T(3,"Gentoo",2002,"Daniel Robbins' source-based distro (grew from Enoch Linux, 2000). Portage and USE flags, inspired by BSD ports."),
  T(4,"Funtoo",2008,"Daniel Robbins' own take on Gentoo after he left the project."),
  T(4,"Sabayon",2005,"Binary-friendly Gentoo desktop; discontinued in 2020."),
  T(4,"Pentoo",2005,"Gentoo with a penetration-testing toolkit."),
  T(4,"Calculate Linux",2007,"Russian Gentoo-based distro with binary packages."),
  T(4,"Exherbo",2008,"Source-based distro started by ex-Gentoo developers; modular and deliberately unconventional."),
  T(4,"Chromium OS",2009,"Google's open-source base of ChromeOS; built with Gentoo's Portage and ebuilds."),
   T(5,"ChromeOS",2011,"Google's Chromebook OS, built on Chromium OS."),
   T(5,"Container Linux",2013,"CoreOS's minimal auto-updating container OS, built from ChromeOS tooling. Retired in 2020."),
    T(6,"Flatcar",2018,"Drop-in successor to CoreOS Container Linux, started by Kinvolk; now a CNCF project."),

 T(3,"Alpine Linux",2005,"musl libc, BusyBox, apk and OpenRC: tiny and a container favourite. Grew out of LEAF."),
  T(4,"postmarketOS",2017,"Real Linux for old smartphones, built on Alpine, with a goal of ten years of support per device."),
 T(3,"NixOS",2003,"Built on the Nix package manager (Eelco Dolstra, 2003): the whole system is declared in config and rollbackable."),
 T(3,"Void Linux",2008,"Juan Romero Pardines' independent distro: runit init, xbps, its own packages, glibc or musl."),
 T(3,"Guix System",2012,"GNU's distro: Guix package manager, Scheme configuration, Shepherd init; free software only."),
 T(3,"Solus",2015,"Independent distro built from scratch; the birthplace of the Budgie desktop."),
 T(3,"OpenWrt",2004,"Embedded Linux for routers; began as replacement firmware for the Linksys WRT54G."),
  T(4,"LEDE",2016,"Linux Embedded Development Environment: a 2016 fork of OpenWrt by core developers, merged back in 2018."),
 T(3,"Puppy Linux",2003,"Barry Kauler's tiny distro that loads entirely into RAM."),
 T(3,"Tiny Core Linux",2008,"About 16 MB, runs from RAM; started by Robert Shingledecker."),
 T(3,"Clear Linux",2015,"Intel's performance-tuned distro; support ended in 2025."),
 T(3,"Android",2008,"Linux kernel with Google's own userland (Bionic libc, ART) and no GNU. The most widely deployed use of the Linux kernel."),
  T(4,"Replicant",2009,"Fully free Android replacement endorsed by the FSF, aiming to remove proprietary drivers."),
  T(4,"CyanogenMod",2009,"Steve Kondik's hugely popular custom ROM. Shut down in 2016."),
   T(5,"LineageOS",2016,"Community continuation of CyanogenMod."),
    T(6,"/e/OS",2018,"De-Googled LineageOS fork by Gael Duval (Mandrake's founder), with its own cloud services."),
  T(4,"GrapheneOS",2019,"Security- and privacy-hardened Android for Pixel phones."),
  T(4,"CalyxOS",2018,"Privacy-focused Android for Pixels, from the Calyx Institute."),
  T(4,"Fire OS",2011,"Amazon's fork of Android for Fire tablets and TV devices, without Google services."),
 T(3,"Qubes OS",2012,"Security through isolation: every app runs in its own Xen VM, using Fedora or Debian templates."),
 T(3,"Linux From Scratch",1999,"A book that walks you through building a whole system from source. Not a distro: a rite of passage."),
 T(3,"KISS Linux",2019,"Dylan Araps' minimalist musl and BusyBox distro with a tiny shell package manager. Development stopped in 2022."),
 T(3,"Sabotage Linux",2011,"musl-based, source-built distro; no systemd, no glibc."),
 T(3,"Bedrock Linux",2012,"Meta-distribution: mix packages from Arch, Debian, Fedora and more in one install."),
 T(3,"GoboLinux",2002,"Rewrites the filesystem hierarchy: every program lives in /Programs/Name/Version."),
 T(3,"SliTaz",2008,"Swiss-French 'tiny' distro with its own tools; runs from RAM."),
 T(3,"Chimera Linux",2021,"musl, LLVM, FreeBSD userland and dinit: a Linux kernel with almost nothing GNU."),
 T(3,"Adelie Linux",2015,"musl-based distro aimed at old and unusual hardware, such as PowerPC Macs."),
 T(3,"OpenELEC",2009,"Just enough OS to run the Kodi media centre."),
  T(4,"LibreELEC",2013,"2013 fork of OpenELEC; the successor after OpenELEC wound down."),
   T(5,"Lakka",2015,"Retro-gaming console OS built on LibreELEC: RetroArch plus a game-console menu."),
 T(3,"webOS",2009,"Palm's Linux-based mobile OS. HP bought it and LG now uses it on its smart TVs."),

 T(2,"BSD",1977,"Berkeley Software Distribution: Bill Joy's additions to Unix, eventually rewritten free of AT&T code (4.4BSD). A cousin of Linux, not a child."),
  T(3,"386BSD",1992,"Bill and Lynne Jolitz's port of BSD to the 386. Stalled patches and legal limbo led to FreeBSD and NetBSD."),
   T(4,"FreeBSD",1993,"Performance and features first: ZFS, jails, bhyve and the permissive BSD licence. The most widely deployed BSD."),
    T(5,"GhostBSD",2010,"FreeBSD with a ready-made MATE desktop and installer."),
    T(5,"NomadBSD",2016,"Live-USB FreeBSD for a portable desktop."),
    T(5,"MidnightBSD",2007,"Desktop-oriented FreeBSD fork by Lucas Holt."),
    T(5,"DragonFly BSD",2003,"Matt Dillon's fork of FreeBSD 4.8, with the HAMMER filesystem and a distinctive SMP design."),
    T(5,"pfSense",2004,"Firewall and router distro on FreeBSD, grown from m0n0wall."),
     T(6,"OPNsense",2014,"2014 fork of pfSense with a cleaner codebase and regular releases."),
    T(5,"FreeNAS",2005,"Storage OS on FreeBSD and ZFS. Became TrueNAS CORE in 2020 (TrueNAS SCALE is Debian-based)."),
    T(5,"Junos OS",1998,"Juniper's router and switch operating system, built on FreeBSD."),
    T(5,"Orbis OS",2013,"The operating system of the PlayStation 4, built on FreeBSD 9."),
   T(4,"NetBSD",1993,"'Of course it runs NetBSD': extreme portability across dozens of CPU architectures."),
    T(5,"OpenBSD",1995,"Theo de Raadt's fork of NetBSD, focused on correctness and security. Gave the world OpenSSH, pf and LibreSSL."),
     T(6,"Bitrig",2012,"OpenBSD fork using LLVM/Clang instead of GCC. Ended in 2018."),
     T(6,"MirBSD",2002,"OpenBSD derivative by Thorsten Glaser; also the home of the mksh shell."),
  S(3,"SunOS",1983,"Sun's BSD-based Unix. SunOS 5 became the kernel part of Solaris (see System V)."),
  T(3,"NeXTSTEP",1989,"Steve Jobs' NeXT: Mach kernel with BSD code and an object-oriented GUI. The base of macOS."),
   T(4,"Darwin",1999,"Open-source core of Apple's systems: the XNU kernel (Mach plus BSD) with a FreeBSD-derived userland."),
    T(5,"macOS",2001,"Mac OS X in 2001; certified UNIX. Apple's desktop OS."),
    T(5,"iOS",2007,"Apple's phone OS, descended from the Darwin core."),

 T(2,"System V",1983,"AT&T's commercial Unix; ancestor of Solaris, AIX and HP-UX."),
  T(3,"Solaris",1992,"Sun's SVR4-based Unix (SunOS 5); known for ZFS, DTrace and zones."),
   T(4,"OpenSolaris",2008,"Sun's open-source Solaris. Oracle closed it again in 2010."),
    T(5,"illumos",2010,"Community fork of the OpenSolaris kernel after Oracle's closure; the base of the illumos distros."),
     T(6,"OpenIndiana",2010,"Community distro continuing OpenSolaris on illumos."),
     T(6,"SmartOS",2011,"Joyent's illumos hypervisor OS: boots from USB or network, runs from RAM, zones plus KVM."),
     T(6,"OmniOS",2012,"Lean illumos server distro, started by OmniTI and now community-run."),
  T(3,"AIX",1986,"IBM's Unix for Power systems, descended from System V."),
  T(3,"HP-UX",1982,"HP's enterprise Unix, for PA-RISC and Itanium."),
  T(3,"UnixWare",1992,"Novell's System V Release 4.2 product; later owned by SCO, centre of the SCO v. IBM lawsuits."),
  T(3,"IRIX",1988,"SGI's Unix for MIPS graphics workstations."),

 T(2,"Plan 9",1992,"Bell Labs' successor to Unix: everything is a file, per-process namespaces, the 9P protocol. UTF-8 was invented here."),
  T(3,"Inferno",1996,"Plan 9 spin-off from Lucent with the Limbo language and a virtual machine."),
  T(3,"9front",2011,"Actively developed community fork of Plan 9."),
  T(3,"Harvey OS",2015,"Plan 9 ported to build with GCC and Clang."),
 T(2,"MINIX",1987,"Andrew Tanenbaum's teaching Unix-like OS. The one Linus Torvalds started on."),
  T(3,"MINIX 3",2005,"Self-healing microkernel version; Intel's management engine reportedly runs a MINIX 3 derivative."),
 T(2,"QNX",1982,"Real-time POSIX microkernel OS, widely used in cars. Unix-like, no Unix code."),
  T(3,"BlackBerry 10",2013,"BlackBerry's QNX-based phone OS; end of life in 2022."),
 T(2,"GNU Hurd",1990,"GNU's Mach-based microkernel system, started in 1990 and still on its way. Debian GNU/Hurd exists."),
 T(2,"Redox OS",2015,"Microkernel Unix-like OS written entirely in Rust, started by Jeremy Soller."),
 T(2,"SerenityOS",2018,"Andreas Kling's from-scratch Unix-like desktop; even the browser (Ladybird) began here."),

 T(0,"CP/M",1974,"Gary Kildall's early microcomputer OS, which DOS was modelled on."),
  T(1,"86-DOS",1980,"Tim Paterson's QDOS for the 8086, bought by Microsoft as the basis of MS-DOS."),
   T(2,"MS-DOS",1981,"Microsoft's PC OS, shipped as PC-DOS on the IBM PC."),
    T(3,"FreeDOS",1994,"Free MS-DOS-compatible clone started by Jim Hall; still handy for BIOS updates and old games."),
  T(1,"DR-DOS",1988,"Digital Research's CP/M-descended answer to MS-DOS."),
 T(0,"VMS",1977,"DEC's operating system for the VAX, led by Dave Cutler."),
  T(1,"OpenVMS",1991,"VMS renamed in 1991; now ported to x86-64 by VSI."),
  T(1,"Windows NT",1993,"Dave Cutler moved from DEC to Microsoft to build it. The base of every modern Windows."),
   T(2,"ReactOS",1996,"Open-source reimplementation of Windows NT, started as FreeWin95."),
 T(0,"BeOS",1995,"Be Inc.'s media OS: pervasive multithreading and the BFS journalling filesystem. Be died in 2001."),
  T(1,"Haiku",2001,"Open-source BeOS reimplementation, started as OpenBeOS; first alpha in 2009."),
  T(1,"ZETA",2005,"yellowTAB's commercial continuation of the BeOS R5 code; ended over licensing doubts."),
 T(0,"AmigaOS",1985,"Commodore's Amiga OS: pre-emptive multitasking on a 1985 home computer."),
  T(1,"AROS",1995,"Open-source reimplementation of the AmigaOS API."),
  T(1,"MorphOS",2002,"PowerPC-native, AmigaOS-compatible OS for Pegasos and Mac hardware."),
  T(1,"AmigaOS 4",2006,"Hyperion's PowerPC AmigaOS."),
 T(0,"MenuetOS",2000,"An entire OS written in assembly that fits on a floppy disk."),
  T(1,"KolibriOS",2004,"MenuetOS fork that stays tiny (1.44 MB) and open source."),
 T(0,"AtheOS",1996,"Kurt Skauen's one-person desktop OS: Unix-like with its own GUI and journalling filesystem."),
  T(1,"Syllable Desktop",2002,"Fork of AtheOS carried on by a community after the author stopped."),
 T(0,"TempleOS",2005,"Terry A. Davis' one-man OS: ring-0 everything, the HolyC language, 640x480 in 16 colours. Renamed several times before 'TempleOS' in 2013."),
  T(1,"ZealOS",2020,"Maintained fork of TempleOS, with UEFI boot and other modernisations."),
 T(0,"Fuchsia",2016,"Google's capability-based OS on the Zircon microkernel. Not Unix-like."),
};

enum { N = sizeof defs / sizeof defs[0] };
_Static_assert(N > 0, "defs[] is empty");

#define MAXD 16
#define NPAL 12
#define PANEL 6
#define NOTE_LINES 3

typedef struct {
    const Def *d;
    int parent, first, last, next, ndesc;
    int family;
    int root;
    int force;
    int visible, open, hidden;
    int x, y, w, ox, oy;
    char label[96];
} Node;

typedef struct { unsigned cp; int attr; } Cell;

static Node nd[N];
static int roots[N], nroots;
static int zoom = 1;
static const int maxdepth[5] = { 3, 4, 5, 99, 99 };
static int colx[MAXD], maxw[MAXD], worldw, worldh;
static int utf8, linux_idx, have_mouse, pal_bold[NPAL];
static int no_color, startup_fold, startup_select = -1, pinned;
static int branch_root = -1, branch_depth;
static int mx = -1, my = -1, sel = -1;
static volatile sig_atomic_t quit_flag;
static Cell *cv;
static int cvw, cvh, camx, camy;

static int build(void)
{
    int stack[MAXD] = { 0 }, prev = -1;
    linux_idx = -1;
    for (int i = 0; i < N; i++) {
        Node *n = &nd[i];
        int dep = defs[i].depth;
        if (dep < 0 || dep >= MAXD || dep > prev + 1) {
            fprintf(stderr, "distrotree: bad depth %d for \"%s\" (entry %d)\n", dep, defs[i].name, i);
            return -1;
        }
        memset(n, 0, sizeof *n);
        n->d = &defs[i];
        n->parent = n->first = n->last = n->next = -1;
        n->family = -1;
        if (dep > 0) {
            int p = stack[dep - 1];
            n->parent = p;
            if (nd[p].first < 0) nd[p].first = i; else nd[nd[p].last].next = i;
            nd[p].last = i;
        } else {
            roots[nroots++] = i;
        }
        stack[dep] = i;
        prev = dep;
        if (linux_idx < 0 && !strcmp(defs[i].name, "Linux")) linux_idx = i;
    }
    if (linux_idx < 0) {
        fputs("distrotree: no \"Linux\" entry\n", stderr);
        return -1;
    }

    int fam = 0;
    for (int i = 0; i < N; i++) {
        Node *n = &nd[i];
        int p = n->parent;
        if (p < 0 || n->d->kind == 2) { n->family = -1; continue; }
        if (nd[p].d->depth == 0 || nd[p].d->kind == 2) {
            n->root = 1;
            n->family = n->first >= 0 ? fam++ : -2;
        } else {
            n->family = nd[p].family;
        }
    }
    for (int i = N - 1; i > 0; i--)
        if (nd[i].parent >= 0) nd[nd[i].parent].ndesc += 1 + nd[i].ndesc;
    return 0;
}

static int eq_ci(const char *a, const char *b)
{
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++;
        b++;
    }
    return *a == *b;
}

static int contains_ci(const char *text, const char *query)
{
    if (!*query) return 1;
    for (; *text; text++) {
        const char *a = text, *b = query;
        while (*a && *b && tolower((unsigned char)*a) == tolower((unsigned char)*b)) {
            a++;
            b++;
        }
        if (!*b) return 1;
    }
    return 0;
}

static int in_scope(int i, int root)
{
    if (root < 0) return 1;
    for (int p = i; p >= 0; p = nd[p].parent)
        if (p == root) return 1;
    return 0;
}

static int find_node(const char *query, int scope)
{
    int partial = -1;
    for (int i = 0; i < N; i++) {
        if (!in_scope(i, scope)) continue;
        if (eq_ci(nd[i].d->name, query)) return i;
        if (partial < 0 && contains_ci(nd[i].d->name, query)) partial = i;
    }
    return partial;
}

static int random_node(int scope)
{
    int count = 0;
    for (int i = 0; i < N; i++)
        if (in_scope(i, scope)) count++;
    if (!count) return -1;
    int pick = rand() % count;
    for (int i = 0; i < N; i++) {
        if (!in_scope(i, scope)) continue;
        if (pick-- == 0) return i;
    }
    return -1;
}

static void show_help(const char *name)
{
    printf(
        "distrotree - an interactive family tree of operating systems\n"
        "\n"
        "usage: %s [options]\n"
        "\n"
        "options:\n"
        "  -h, --help                 show this help\n"
        "  --dump [0-4]               print the tree instead of opening the UI\n"
        "  --no-color                 disable colours\n"
        "  --random                   select a random system\n"
        "  --branch NAME              show only a system and its descendants\n"
        "  --search NAME              find and select a system by name\n"
        "  --full-fold                start with every branch folded\n"
        "  --full-unfold              start with every branch unfolded\n"
        "\n"
        "searches are case-insensitive and accept partial names. --branch and\n"
        "--search can be combined; --random can be used with --branch.\n"
        "\n"
        "mouse: hover to read, click to fold, wheel to scroll, ctrl+wheel to zoom\n"
        "keys:  arrows/hjkl pan, +/- zoom, Enter fold, c collapse, a expand, 0 reset, q quit\n",
        name
    );
}

static int rowstep(void) { return zoom >= 4 ? 2 : 1; }

static void lay(int i, int *row)
{
    Node *n = &nd[i];
    n->visible = 1;
    int want = n->d->depth - branch_depth < maxdepth[zoom];
    if (n->force == 1) want = 0;
    else if (n->force == 2) want = 1;
    n->open = n->first >= 0 && want;
    n->hidden = (n->first >= 0 && !n->open) ? n->ndesc : 0;
    int len = snprintf(n->label, sizeof n->label, "%s", n->d->name);
    if (zoom >= 3 && n->d->year)
        len += snprintf(n->label + len, sizeof n->label - len, " (%d)", n->d->year);
    if (n->hidden)
        snprintf(n->label + len, sizeof n->label - len, " [+%d]", n->hidden);
    n->w = (int)strlen(n->label);
    if (!n->open) {
        n->y = (*row)++ * rowstep();
        return;
    }
    for (int c = n->first; c >= 0; c = nd[c].next) lay(c, row);
    n->y = (nd[n->first].y + nd[n->last].y) / 2;
}

static void layout(void)
{
    int row = 0, maxd = 0, maxy = 0;
    for (int i = 0; i < N; i++) nd[i].visible = 0;
    if (branch_root >= 0) {
        lay(branch_root, &row);
    } else {
        for (int r = 0; r < nroots; r++) {
            lay(roots[r], &row);
            row++;
        }
    }
    memset(maxw, 0, sizeof maxw);
    for (int i = 0; i < N; i++) {
        if (!nd[i].visible) continue;
        int d = nd[i].d->depth - branch_depth;
        if (nd[i].w > maxw[d]) maxw[d] = nd[i].w;
        if (d > maxd) maxd = d;
        if (nd[i].y > maxy) maxy = nd[i].y;
    }
    worldh = maxy + 1;
    int gap = zoom >= 3 ? 7 : 5;
    colx[0] = 0;
    for (int d = 1; d <= maxd; d++) colx[d] = colx[d - 1] + maxw[d - 1] + gap;
    for (int i = 0; i < N; i++)
        if (nd[i].visible) nd[i].x = colx[nd[i].d->depth - branch_depth];
    worldw = colx[maxd] + maxw[maxd];
}

static const unsigned G[16] = {
    ' ', 0x2502, 0x2502, 0x2502, 0x2500, 0x2518, 0x2510, 0x2524,
    0x2500, 0x2514, 0x250C, 0x251C, 0x2500, 0x2534, 0x252C, 0x253C
};

static void cput(int y, int x, unsigned cp, int attr)
{
    y -= camy;
    x -= camx;
    if (y < 0 || y >= cvh || x < 0 || x >= cvw) return;
    cv[y * cvw + x].cp = cp;
    cv[y * cvw + x].attr = attr;
}

static void ctext(int y, int x, const char *s, int attr)
{
    for (; *s; s++, x++) cput(y, x, (unsigned char)*s, attr);
}

static int fattr(int i)
{
    Node *n = &nd[i];
    if (n->d->kind == 1) return A_DIM;
    if (n->family == -1) return A_BOLD;
    if (n->family == -2 || no_color) return A_NORMAL;
    int k = n->family % NPAL;
    int a = COLOR_PAIR(k + 1);
    if (pal_bold[k]) a |= A_BOLD;
    return a;
}

static void draw_tree(int hl)
{
    for (int i = 0; i < cvw * cvh; i++) {
        cv[i].cp = ' ';
        cv[i].attr = 0;
    }
    for (int p = 0; p < N; p++) {
        Node *pn = &nd[p];
        if (!pn->visible || !pn->open) continue;
        int ymin = nd[pn->first].y, ymax = nd[pn->last].y;
        int vx = nd[pn->first].x - 3, pa = fattr(p);
        for (int x = pn->x + pn->w + 1; x < vx; x++) cput(pn->y, x, 0x2500, pa);
        for (int r = ymin; r <= ymax; r++) {
            int mask = 0, child = -1;
            if (r > ymin) mask |= 1;
            if (r < ymax) mask |= 2;
            if (r == pn->y) mask |= 4;
            for (int c = pn->first; c >= 0; c = nd[c].next)
                if (nd[c].y == r) { child = c; break; }
            if (child >= 0) mask |= 8;
            if (!mask) continue;
            cput(r, vx, G[mask], child >= 0 ? fattr(child) : pa);
            if (child >= 0) cput(r, vx + 1, 0x2500, fattr(child));
        }
    }
    for (int i = 0; i < N; i++) {
        Node *n = &nd[i];
        if (!n->visible) continue;
        int a = fattr(i);
        if (n->root || n->d->kind == 2 || n->d->depth == 0) a |= A_BOLD;
        if (i == hl) a |= A_REVERSE;
        ctext(n->y, n->x, n->label, a);
    }
}

static int enc(unsigned cp, char *b)
{
    if (cp < 0x80) {
        b[0] = (char)cp;
        b[1] = 0;
        return 1;
    }
    if (cp < 0x800) {
        b[0] = (char)(0xC0 | (cp >> 6));
        b[1] = (char)(0x80 | (cp & 63));
        b[2] = 0;
        return 2;
    }
    b[0] = (char)(0xE0 | (cp >> 12));
    b[1] = (char)(0x80 | ((cp >> 6) & 63));
    b[2] = (char)(0x80 | (cp & 63));
    b[3] = 0;
    return 3;
}

static chtype acs_for(unsigned cp)
{
    switch (cp) {
    case 0x2500: return ACS_HLINE;
    case 0x2502: return ACS_VLINE;
    case 0x2518: return ACS_LRCORNER;
    case 0x2510: return ACS_URCORNER;
    case 0x2514: return ACS_LLCORNER;
    case 0x250C: return ACS_ULCORNER;
    case 0x2524: return ACS_RTEE;
    case 0x251C: return ACS_LTEE;
    case 0x2534: return ACS_BTEE;
    case 0x252C: return ACS_TTEE;
    case 0x253C: return ACS_PLUS;
    default:     return '?';
    }
}

static void blit(void)
{
    for (int y = 0; y < cvh; y++) {
        for (int x = 0; x < cvw; x++) {
            Cell c = cv[y * cvw + x];
            if (c.cp == ' ') continue;
            attrset(c.attr);
            if (c.cp < 0x80) {
                mvaddch(y, x, (chtype)c.cp);
                continue;
            }
            int done = 0;
            if (utf8) {
                wchar_t w[2] = { (wchar_t)c.cp, 0 };
                cchar_t cc;
                memset(&cc, 0, sizeof cc);
                if (setcchar(&cc, w, (attr_t)(c.attr & ~A_COLOR), (short)PAIR_NUMBER(c.attr), NULL) == OK
                    && mvadd_wch(y, x, &cc) == OK)
                    done = 1;
            }
            if (!done) mvaddch(y, x, acs_for(c.cp));
        }
    }
    attrset(A_NORMAL);
}

static void wrapn(const char *s, int w, char l[NOTE_LINES][256])
{
    if (w > 250) w = 250;
    if (w < 8) w = 8;
    int len = (int)strlen(s);
    for (int li = 0; li < NOTE_LINES; li++) l[li][0] = 0;
    for (int li = 0; li < NOTE_LINES && len > 0; li++) {
        int n = len;
        if (len > w) {
            n = w;
            int k = w;
            while (k > 0 && s[k] != ' ') k--;
            if (k > 0) n = k;
        }
        memcpy(l[li], s, n);
        l[li][n] = 0;
        s += n;
        len -= n;
        while (*s == ' ') {
            s++;
            len--;
        }
    }
    if (len > 0) {
        char *last = l[NOTE_LINES - 1];
        int L = (int)strlen(last);
        if (L >= 3) strcpy(last + L - 3, "...");
    }
}

static void panel(int f)
{
    int W = COLS, y0 = LINES - PANEL, tw = W - 2;
    if (y0 < 0 || tw < 1) return;
    for (int r = 0; r < PANEL; r++) {
        move(y0 + r, 0);
        clrtoeol();
    }
    if (f >= 0) {
        Node *n = &nd[f];
        int chain[MAXD + 1], k = 0;
        char path[1024] = "";
        for (int i = f; i >= 0 && k <= MAXD; i = nd[i].parent) chain[k++] = i;
        for (int j = k - 1; j >= 0; j--) {
            strcat(path, nd[chain[j]].d->name);
            if (j) strcat(path, " > ");
        }
        int pl = (int)strlen(path);
        const char *ps = pl > tw ? path + pl - tw : path;
        attron(A_BOLD);
        mvaddnstr(y0, 1, ps, tw);
        attroff(A_BOLD);

        attron(fattr(f) | A_BOLD);
        mvprintw(y0 + 1, 1, "%s (%d)", n->d->name, n->d->year);
        attroff(fattr(f) | A_BOLD);
        if (n->ndesc > 0) printw("   %d descendant%s", n->ndesc, n->ndesc == 1 ? "" : "s");
        if (n->first >= 0) printw("   [%s: %s]", have_mouse ? "click" : "Enter", n->open ? "fold" : "unfold");

        char l[NOTE_LINES][256];
        wrapn(n->d->note, tw, l);
        for (int i = 0; i < NOTE_LINES; i++) mvaddnstr(y0 + 2 + i, 1, l[i], tw);
    } else {
        char s[96];
        snprintf(s, sizeof s, "%d systems in the tree", N);
        attron(A_BOLD);
        mvaddnstr(y0, 1, s, tw);
        attroff(A_BOLD);
        mvaddnstr(y0 + 1, 1, "Hover a name with the mouse to read its story.", tw);
        mvaddnstr(y0 + 2, 1, "Click or Enter folds a branch. Wheel scrolls, ctrl+wheel or +/- zooms.", tw);
        mvaddnstr(y0 + 3, 1, "c collapses to an overview, a expands everything, 0 resets the view.", tw);
    }
    char bar[512];
    int bw = W < 511 ? W : 511;
    snprintf(bar, sizeof bar, "%-*s", bw, " arrows/hjkl pan | wheel scroll | +/- zoom | click fold | c/a all | 0 reset | q quit");
    char z[32];
    snprintf(z, sizeof z, "zoom %d/5 ", zoom + 1);
    int zl = (int)strlen(z);
    if (bw > zl + 2) memcpy(bar + bw - zl, z, zl);
    attron(A_REVERSE);
    mvaddnstr(y0 + PANEL - 1, 0, bar, bw);
    attroff(A_REVERSE);
}

static int find_focus(void)
{
    int cx = camx + cvw / 2, cy = camy + cvh / 2, best = -1, bc = 1 << 30;
    for (int i = 0; i < N; i++) {
        Node *n = &nd[i];
        if (!n->visible) continue;
        int dx = cx < n->x ? n->x - cx : cx > n->x + n->w - 1 ? cx - (n->x + n->w - 1) : 0;
        int dy = abs(n->y - cy);
        int c = dx + dy * 4;
        if (c < bc) {
            bc = c;
            best = i;
        }
    }
    return best;
}

static int hit(int sx, int sy)
{
    if (sx < 0 || sy < 0 || sx >= cvw || sy >= cvh) return -1;
    int wx = sx + camx, wy = sy + camy;
    for (int i = 0; i < N; i++) {
        Node *n = &nd[i];
        if (n->visible && n->y == wy && wx >= n->x && wx < n->x + n->w) return i;
    }
    return -1;
}

static void clamp_cam(void)
{
    if (worldw + 12 <= cvw) {
        camx = -(cvw - worldw) / 2;
    } else {
        if (camx < -6) camx = -6;
        if (camx > worldw - cvw + 6) camx = worldw - cvw + 6;
    }
    if (worldh + 2 <= cvh) {
        camy = -(cvh - worldh) / 2;
    } else {
        if (camy < -1) camy = -1;
        if (camy > worldh - cvh + 1) camy = worldh - cvh + 1;
    }
}

static void save_old(void)
{
    for (int i = 0; i < N; i++) {
        nd[i].ox = nd[i].x;
        nd[i].oy = nd[i].y;
    }
}

static void reanchor(int f, int ocx, int ocy)
{
    int a = f;
    while (!nd[a].visible && nd[a].parent >= 0) a = nd[a].parent;
    camx = nd[a].x - (nd[a].ox - ocx);
    camy = nd[a].y - (nd[a].oy - ocy);
}

static int anchor_node(void)
{
    int a = hit(mx, my);
    if (a < 0 && sel >= 0 && nd[sel].visible) a = sel;
    if (a < 0) a = find_focus();
    return a;
}

static void zoom_by(int dz, int ocx, int ocy)
{
    int nz = zoom + dz, a = anchor_node();
    if (nz < 0 || nz > 4 || a < 0) return;
    save_old();
    zoom = nz;
    layout();
    reanchor(a, ocx, ocy);
}

static void toggle(int f, int ocx, int ocy)
{
    if (f < 0 || nd[f].first < 0) return;
    save_old();
    nd[f].force = nd[f].open ? 1 : 2;
    layout();
    reanchor(f, ocx, ocy);
}

static void set_all(int expand, int ocx, int ocy)
{
    int a = anchor_node();
    save_old();
    for (int i = 0; i < N; i++) {
        int keep_open = expand || i == branch_root || nd[i].d->depth == 0 || nd[i].d->kind == 2;
        nd[i].force = keep_open ? 2 : 1;
    }
    layout();
    if (a >= 0) reanchor(a, ocx, ocy);
}

static void home(void)
{
    zoom = 1;
    for (int i = 0; i < N; i++) nd[i].force = 0;
    layout();
    int focus = branch_root >= 0 ? branch_root : linux_idx;
    camx = -3;
    camy = nd[focus].y - cvh / 2;
}

static void resize_canvas(void)
{
    int h = LINES - PANEL;
    if (h < 1) h = 1;
    if (h != cvh || COLS != cvw || !cv) {
        Cell *p = realloc(cv, sizeof(Cell) * (size_t)COLS * (size_t)h);
        if (!p) {
            endwin();
            fputs("distrotree: out of memory\n", stderr);
            exit(1);
        }
        cv = p;
        cvw = COLS;
        cvh = h;
    }
}

static int dump(void)
{
    layout();
    cvw = worldw + 2;
    cvh = worldh + 1;
    cv = malloc(sizeof(Cell) * (size_t)cvw * (size_t)cvh);
    if (!cv) {
        fputs("distrotree: out of memory\n", stderr);
        return 1;
    }
    camx = camy = 0;
    draw_tree(-1);
    char b[4];
    for (int y = 0; y < cvh; y++) {
        int last = -1;
        for (int x = 0; x < cvw; x++)
            if (cv[y * cvw + x].cp != ' ') last = x;
        for (int x = 0; x <= last; x++) {
            enc(cv[y * cvw + x].cp, b);
            fputs(b, stdout);
        }
        putchar('\n');
    }
    free(cv);
    return 0;
}

static void apply_startup_fold(void)
{
    if (startup_fold) {
        for (int i = 0; i < N; i++)
            nd[i].force = (startup_fold == 1 && i == branch_root) ? 2 : startup_fold;
    }
    if (startup_select >= 0) {
        for (int p = nd[startup_select].parent; p >= 0; p = nd[p].parent)
            nd[p].force = 2;
    }
    layout();
}

static void on_signal(int s)
{
    (void)s;
    quit_flag = 1;
}

static void shutdown_ui(void)
{
    if (have_mouse) {
        fputs("\033[?1003l", stdout);
        fflush(stdout);
    }
    endwin();
}

static void init_colors(void)
{
    if (no_color || !has_colors()) return;
    start_color();
    int bg = use_default_colors() == OK ? -1 : COLOR_BLACK;
    static const short c8[6] = { COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_MAGENTA, COLOR_YELLOW };
    static const short c256[NPAL] = { 167, 75, 71, 80, 176, 221, 208, 141, 114, 39, 211, 180 };
    int wide = COLORS >= 256;
    for (int k = 0; k < NPAL; k++) {
        init_pair((short)(k + 1), wide ? c256[k] : c8[k % 6], (short)bg);
        pal_bold[k] = wide ? 0 : (k >= 6 || k % 6 == 1);
    }
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    const char *cs = nl_langinfo(CODESET);
    utf8 = cs && (strstr(cs, "UTF-8") || strstr(cs, "utf8") || strstr(cs, "UTF8"));

    int dump_mode = 0, dump_zoom = 3, random_mode = 0;
    const char *branch_arg = NULL, *search_arg = NULL;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            show_help(argv[0]);
            return 0;
        } else if (!strcmp(argv[i], "--no-color")) {
            no_color = 1;
        } else if (!strcmp(argv[i], "--full-fold")) {
            startup_fold = 1;
        } else if (!strcmp(argv[i], "--full-unfold")) {
            startup_fold = 2;
        } else if (!strcmp(argv[i], "--random")) {
            random_mode = 1;
        } else if (!strcmp(argv[i], "--branch")) {
            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                fputs("distrotree: --branch requires a system name\n", stderr);
                return 1;
            }
            branch_arg = argv[++i];
        } else if (!strcmp(argv[i], "--search")) {
            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                fputs("distrotree: --search requires a system name\n", stderr);
                return 1;
            }
            search_arg = argv[++i];
        } else if (!strcmp(argv[i], "--dump")) {
            dump_mode = 1;
            if (i + 1 < argc && argv[i + 1][0] != '-') dump_zoom = atoi(argv[++i]);
        } else {
            fprintf(stderr, "distrotree: unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    if (random_mode && search_arg) {
        fputs("distrotree: --random and --search cannot be used together\n", stderr);
        return 1;
    }

    if (build() != 0) return 1;

    if (branch_arg) {
        branch_root = find_node(branch_arg, -1);
        if (branch_root < 0) {
            fprintf(stderr, "distrotree: no system matching branch name \"%s\"\n", branch_arg);
            return 1;
        }
        branch_depth = nd[branch_root].d->depth;
    }

    if (search_arg) {
        startup_select = find_node(search_arg, branch_root);
        if (startup_select < 0) {
            fprintf(stderr, "distrotree: no system matching search \"%s\"\n", search_arg);
            return 1;
        }
    } else if (random_mode) {
        srand((unsigned)time(NULL));
        startup_select = random_node(branch_root);
    } else if (branch_root >= 0) {
        startup_select = branch_root;
    }

    if (dump_mode) {
        zoom = dump_zoom;
        if (zoom < 0) zoom = 0;
        if (zoom > 4) zoom = 4;
        apply_startup_fold();
        return dump();
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_handler = on_signal;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGHUP, &sa, NULL);

    if (!initscr()) {
        fputs("distrotree: cannot initialise terminal\n", stderr);
        return 1;
    }
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(250);
    init_colors();
    mouseinterval(0);
    have_mouse = mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL) != 0;
    if (have_mouse) {
        fputs("\033[?1003h", stdout);
        fflush(stdout);
    }
    resize_canvas();
    home();
    apply_startup_fold();

    if (startup_select >= 0) {
        sel = startup_select;
        pinned = 1;
        camx = nd[sel].x - cvw / 2;
        camy = nd[sel].y - cvh / 2;
    }

    int dirty = 1;
    while (!quit_flag) {
        if (dirty) {
            resize_canvas();
            layout();
            clamp_cam();
            if (!have_mouse) {
                if (!pinned || sel < 0 || !nd[sel].visible) {
                    sel = find_focus();
                    pinned = 0;
                }
            } else {
                if (sel >= 0 && !nd[sel].visible) sel = -1;
                int h = hit(mx, my);
                if (h >= 0) sel = h;
            }
            erase();
            draw_tree(sel);
            blit();
            panel(sel);
            refresh();
            dirty = 0;
        }

        int ch = getch();
        if (ch == ERR) continue;
        dirty = 1;
        if (ch != KEY_RESIZE) pinned = 0;
        int ocx = camx, ocy = camy;
        switch (ch) {
        case 'q': case 'Q': quit_flag = 1; break;
        case KEY_LEFT:  case 'h': camx -= 6; break;
        case KEY_RIGHT: case 'l': camx += 6; break;
        case KEY_UP:    case 'k': camy -= 3; break;
        case KEY_DOWN:  case 'j': camy += 3; break;
        case KEY_SLEFT:  case 'H': camx -= 24; break;
        case KEY_SRIGHT: case 'L': camx += 24; break;
        case KEY_SR:     case 'K': camy -= 12; break;
        case KEY_SF:     case 'J': camy += 12; break;
        case KEY_PPAGE: camy -= cvh - 2; break;
        case KEY_NPAGE: camy += cvh - 2; break;
        case '+': case '=': zoom_by(+1, ocx, ocy); break;
        case '-': case '_': zoom_by(-1, ocx, ocy); break;
        case '\n': case '\r': case KEY_ENTER: case ' ':
            toggle(sel, ocx, ocy);
            break;
        case 'c': set_all(0, ocx, ocy); break;
        case 'a': set_all(1, ocx, ocy); break;
        case '0': case KEY_HOME: home(); break;
        case KEY_MOUSE: {
            MEVENT ev;
            if (getmouse(&ev) != OK) break;
            mx = ev.x;
            my = ev.y;
            mmask_t b = ev.bstate;
            int up = (b & BUTTON4_PRESSED) != 0, down = 0;
#ifdef BUTTON5_PRESSED
            down = (b & BUTTON5_PRESSED) != 0;
#endif
            if (up || down) {
                int dir = up ? -1 : 1;
                if (b & BUTTON_CTRL) zoom_by(-dir, ocx, ocy);
                else if (b & BUTTON_SHIFT) camx += dir * 8;
                else camy += dir * 3;
            } else if (b & (BUTTON1_PRESSED | BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED)) {
                int h = hit(mx, my);
                if (h >= 0) {
                    sel = h;
                    toggle(h, ocx, ocy);
                }
            }
            break;
        }
        case KEY_RESIZE: break;
        default: break;
        }
    }
    shutdown_ui();
    return 0;
}
