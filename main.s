        .gba
        .thumb
        .open "roms/BPRE0.gba","build/jimmy_version.gba", 0x08000000

        .include "patches/bike_hooks.s"

        .org 0x08800000
        .importobj "build/linked.o"
        .close
