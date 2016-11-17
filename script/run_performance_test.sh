#!/bin/bash

bash ./script/build_libds.sh RELEASE X86_64 LIBC ELF
exec ./output/bin/ds.elf -p=50000 *.*.*

