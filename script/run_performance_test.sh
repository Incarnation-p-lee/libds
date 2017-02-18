#!/bin/bash

bash make clean make RELEASE=1
./output/bin/ds.elf -p=50000 *.*.*

