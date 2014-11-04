.SUFFIXES:
.SUFFIXES: .o .a .so .h .c .s .S

SHELL        =/bin/sh
CC           =gcc
#CFLAG        =-Wall -Werror -c
CFLAG        =-c
CFLAG        +=$(ARGV_CFG)
LFLAG        =
LFLAG        +=$(ARGV_LNK)
TARGET       =ds.elf
EXTLIB       =-lm
