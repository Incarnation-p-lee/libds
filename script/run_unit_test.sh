#!/bin/bash

bash ./script/build.sh DEBUG X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -u *.*.*
lcov --directory . --capture --output-file unit_test.info

bash ./script/build.sh RELEASE X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -p=100 *.*.*
lcov --directory . --capture --output-file performance_test.info

lcov --add-tracefile unit_test.info --add-tracefile performance_test.info --output-file coverage.info
rm -v *.gcno

