#!/bin/bash

make clean && make COVERAGE=1
./bin/ds.elf -l -u -p=1000 *.*.*

