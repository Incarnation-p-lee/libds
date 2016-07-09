#!/bin/bash

lcovrc=-rc lcov_branch_coverage=1 

bash ./script/build.sh DEBUG X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -u *.*.*
lcov --directory . --capture $lcover --output-file unit_test.info

bash ./script/build.sh RELEASE X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -p=100 *.*.*
lcov --directory . --capture $lcover --output-file performance_test.info

lcov --add-tracefile unit_test.info --add-tracefile performance_test.info --output-file coverage.info
cp -v coverage.info /tmp/coverage.info
rm -v *.gcno