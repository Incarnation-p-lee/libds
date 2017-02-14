.SUFFIXES:
.SUFFIXES: .o .a .so .h .c .s .S

## command define ##
SHELL  :=/bin/sh
AR     :=ar
CC     :=gcc
LD     :=gcc
MV     :=mv -v
CP     :=cp -v
RM     :=rm -f
MKDIR  :=mkdir -v

## compile options ##
AFLAG  :=
CFLAG  :=-Wall -Wextra -Werror -c
LFLAG  :=-Wl,--warn-common


## sub-module source files ##
src    :=

obj    =$(subst .c,.o, $(src))     # use recursive variable here
lib    :=-lm

## dependency config ##
out    :=bin
inc    :=src/inc
CFLAG  +=$(addprefix -I,$(inc))
CFLAG  +=-DX86_64 -DLIBC -DDEBUG

## command wrapper ##
WP_CC  :='echo "   Compile $<" && $(CC)'

vpath %.h $(inc)

all:

include src/makefile.mk
include src/common/makefile.mk
include src/hash/makefile.mk
include src/heap/makefile.mk
include src/linked_list/makefile.mk
include src/queue/makefile.mk
include src/set/makefile.mk
include src/sort/makefile.mk
include src/stack/makefile.mk
include src/test/makefile.mk
include src/tree/makefile.mk

TARGET :=$(addprefix $(out)/, ds.elf)


.PHONY:all
all:$(TARGET)


$(TARGET):$(obj)
ifneq ($(out), $(wildcard $(out)))
	@$(MKDIR) $(out)
endif
	@echo "    Link $@"
	@$(CC) $(LFLAG) $? -o $@ $(lib)

$(obj):%.o:%.c
	@echo "    Compile $(notdir $<)"
	@$(CC) $(CFLAG) $< -o $@

.PHONY:clean
clean:
	@echo "     Clean Object"
	@$(RM) $(obj)


## define list ##

