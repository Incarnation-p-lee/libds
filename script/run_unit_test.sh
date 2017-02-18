#!/bin/bash

lcovrc=-rc lcov_branch_coverage=1 

bash make clean make COVERAGE=1
./bin/ds.elf -u *.*.*
lcov --directory . --capture $lcover --output-file unit_test.info

bash make clean make RELEASE=1 COVERAGE=1
./output/bin/ds.elf -p=100 *.*.*
lcov --directory . --capture $lcover --output-file performance_test.info

lcov --add-tracefile unit_test.info --add-tracefile performance_test.info --output-file coverage.info
cp -v coverage.info /tmp/coverage.info
rm -v *.gcno
