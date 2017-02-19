#!/bin/bash

lcover="-rc lcov_branch_coverage=1"
git clean -f

make clean && make COVERAGE=1
./bin/ds.elf -u *.*.*
lcov --directory . --capture $lcover --output-file unit_test.info

make clean && make RELEASE=1 COVERAGE=1
./bin/ds.elf -p=10 *.*.*
lcov --directory . --capture $lcover --output-file performance_test.info

## copy *.gcno file to current ##
gcno_list=`find src/ | grep -E "(gcno|gcda)$"`
for gcno in ${gcno_list[@]}
do
    cp $gcno .
done

lcov --add-tracefile unit_test.info --add-tracefile performance_test.info --output-file coverage.info
cp -v coverage.info /tmp/coverage.info

