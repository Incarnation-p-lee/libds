#!/bin/bash

bash ./script/build.sh DEBUG X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -u linked_list.*.*
lcov --directory . --capture --output-file coverage.info
mv coverage.info /tmp/unit_test.info
ls /tmp/unit_test.info
file /tmp/unit_test.info

bash ./script/build.sh RELEASE X86_64 LIBC ELF COVERAGE
./output/out/ds.elf -p=10000 linked_list.*.*
lcov --directory . --capture --output-file coverage.info
mv coverage.info /tmp/performance_test.info
ls /tmp/performance_test.info
file /tmp/performance_test.info

