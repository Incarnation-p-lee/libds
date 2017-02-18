.SUFFIXES:
.SUFFIXES: .o .a .so .h .c .s .S

## command define ##
SHELL                  :=/bin/sh
AR                     :=ar
CC                     :=$(if $(V), gcc, @gcc)
LD                     :=$(CC)
MV                     :=mv -v
CP                     :=cp -v
RM                     :=rm -f
MKDIR                  :=mkdir -v
PERL                   :=$(if $(V), perl, @perl)

## compile options ##
AFLAG                  :=-rcs
CFLAG                  :=-Wall -Wextra -Werror -fPIC -c
LFLAG                  :=-Wl,--warn-common
SLFLAG                 :=$(LFLAG) -shared

## sub-module source files ##
src                    :=

obj                    =$(subst .c,.o, $(src))       # use recursive variable here
obj_partial            =$(filter-out %main.o, $(obj)) # excluded main.o
lib                    :=-lm

## dependency config ##
out                    :=bin
inc                    :=src/inc
script                 :=script
script_module_decl     :=$(script)/produce_module_declaration_h.pl
script_universal       :=$(script)/produce_universal_h.pl
script_interface       :=$(script)/produce_data_structure_interface_h.pl

vpath %.h $(inc)

## first target should be in front of sub-makefile
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

TARGET_ELF             :=$(addprefix $(out)/, ds.elf)
TARGET_A               :=$(addprefix $(out)/, libds.a)
TARGET_SO              :=$(addprefix $(out)/, libds.so)

CFLAG                  +=$(addprefix -I,$(inc))
CFLAG                  +=-DX86_64 -DLIBC

CF_DEBUG               :=-DDEBUG -g
CF_RELEASE             :=-O3 -ofast
CF_COVERAGE            :=--coverage

## RELEASE build ##
CFLAG                  +=$(if $(RELEASE),$(CF_RELEASE),$(CF_DEBUG))
LFLAG                  +=$(if $(RELEASE),$(CF_RELEASE),$(CF_DEBUG))
SLFLAG                 +=$(if $(RELEASE),$(CF_RELEASE),$(CF_DEBUG))

## COVERAGE build ##
CFLAG                  +=$(if $(COVERAGE),$(CF_COVERAGE),)
lib                    +=$(if $(COVERAGE),-lgcov,)

.PHONY:all help clean depend

all:depend $(TARGET_ELF) $(TARGET_A) $(TARGET_SO)

depend:
	$(if $(wildcard $(out)), , $(MKDIR) $(out))
	$(PERL) $(script_module_decl) $(if $(RELEASE),"No","Yes")
	$(PERL) $(script_universal)
	$(PERL) $(script_interface)

## .elf target ##
$(TARGET_ELF):$(obj)
	@echo "    Link     $@"
	$(CC) $(LFLAG) $? -o $@ $(lib)

## .a target ##
$(TARGET_A):$(obj_partial)
	@echo "    Archive  $@"
	@$(AR) $(AFLAG) $@ $?

## .so target ##
$(TARGET_SO):$(obj_partial)
	@echo "    Shared   $@"
	$(CC) $(SLFLAG) $? -o $@ $(lib)

## object ##
$(obj):%.o:%.c
	@echo "    Compile  $(notdir $<)"
	$(CC) $(CFLAG) $< -o $@

clean:
	@echo "    Clean Object"
	@$(RM) $(obj)

help:
	@echo
	@echo "  make            :Default debug build"
	@echo "  make RELEASE=1  :Release build"
	@echo "  make V=1        :Verbose build"
	@echo "  make COVERAGE=1 :Coverage build"
	@echo

