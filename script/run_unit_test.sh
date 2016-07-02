#!/bin/bash

bash ./script/build.sh DEBUG X86_64 LIBC ELF COVERAGE
exec ./output/out/ds.elf -u linked_list.*.*

bash ./script/build.sh RELEASE X86_64 LIBC ELF COVERAGE
exec ./output/out/ds.elf -p=10000 linked_list.*.*

