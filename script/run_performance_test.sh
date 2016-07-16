#!/bin/bash

bash ./script/build_libds.sh RELEASE X86_64 LIBC ELF
exec ./output/out/ds.elf -p=50000 *.*.*

