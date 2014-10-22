#!/bin/sh
qemu-system-i386 -kernel build/sheaf.bin -drive file=fat:rw:drive/
