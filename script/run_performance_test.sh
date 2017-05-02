#!/bin/bash

make clean && make RELEASE=1
./bin/ds.elf -p=100000 *.*.*

