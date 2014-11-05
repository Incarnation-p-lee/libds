.SUFFIXES:
.SUFFIXES: .o .a .so .h .c .s .S

SHELL        =/bin/sh
CC           =gcc
AR           =ar
AFLAG        =-rc

DFLAG        =-shared
DFLAG        +=$(ARGV_DFG)

#CFLAG        =-Wall -Werror -c
CFLAG        =-c
CFLAG        +=$(ARGV_CFG)

LFLAG        =
LFLAG        +=$(ARGV_LNK)

TARGET       =ds.elf
STLIB        =libds.a
DYLIB        =libds.so
EXTLIB       =-lm
EXTLIB       +=$(ARGV_LIB)
LIBOBJ       =linked_list.o
