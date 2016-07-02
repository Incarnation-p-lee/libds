#!/bin/bash

./script/build.sh RELEASE X86_64 LIBC ELF
./output/out/ds.elf -p=50000 linked_list.*.*

