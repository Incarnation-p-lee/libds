#!/bin/bash

bash ./script/build.sh DEBUG X86_64 LIBC ELF COVERAGE
exec ./output/out/ds.elf -u linked_list.*.*
lcov --directory . --capture --output-file coverage.info
mv coverage.info unit_test.info

bash ./script/build.sh RELEASE X86_64 LIBC ELF COVERAGE
exec ./output/out/ds.elf -p=10000 linked_list.*.*
lcov --directory . --capture --output-file coverage.info
mv coverage.info performance_test.info

