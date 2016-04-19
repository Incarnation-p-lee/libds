.SUFFIXES:
.SUFFIXES: .o .a .so .h .c .s .S

SHELL        =/bin/sh
CC           =gcc
# CC           =clang-3.5
AR           =ar
AFLAG        =-rc

DFLAG        =-shared -fPIC

#CFLAG        =-Wall -Werror -c -fPIC
CFLAG        =-c -fPIC
CFLAG        +=$(ARGV_CFG)

LFLAG        =
LFLAG        +=$(ARGV_LNK)

TARGET       =ds.elf
STLIB        =libds.a
DYLIB        =libds.so
EXTLIB       =-lm
EXTLIB       +=$(ARGV_LIB)

# update this library object for new data structure
LIBOBJ       =linked_list.o stack.o log.o queue.o tree.o common.o hash.o heap.o
