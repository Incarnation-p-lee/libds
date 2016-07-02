#!/bin/bash

./script/build.sh DEBUG X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -u linked_list.*.*

./script/build.sh RELEASE X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -p=10000 linked_list.*.*

