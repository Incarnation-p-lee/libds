#!/bin/bash

bash ./script/build.sh DEBUG X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -u *.*.*
lcov --directory . --capture --output-file coverage.info
mv coverage.info unit_test.info

bash ./script/build.sh RELEASE X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -p=10000 *.*.*
lcov --directory . --capture --output-file coverage.info
mv coverage.info performance_test.info

lcov --add-tracefile unit_test.info --add-tracefile performance_test.info --output-file coverage.info
rm -v *.gcno

