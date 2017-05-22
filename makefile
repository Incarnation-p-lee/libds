## command define ##
AR                     :=ar
CC                     :=$(if $(V), gcc, @gcc)
RM                     :=rm -f
MKDIR                  :=$(if $(V), mkdir, @mkdir)
PERL                   :=$(if $(V), perl, @perl)

## compile options ##
AFLAG                  :=-rcs
CFLAG                  :=-Wall -Wextra -Werror -fPIC -c
LFLAG                  :=-Wl,--warn-common
SLFLAG                 :=$(LFLAG) -shared

## sub-module source files ##
src                    :=
obj                    =$(subst .c,.o, $(src))        # use recursive variable here
dep                    =$(subst .c,.d,$(src))
obj_partial            =$(filter-out %main.o, $(obj)) # excluded main.o
decl                   =$(subst .o,_declaration.h,$(obj_partial))
decl_partial           =$(filter-out %test_declaration.h, $(decl))

lib                    :=-lm
lib                    +=$(if $(COVERAGE),-lgcov,)

## dependency config ##
out                    :=bin
base                   :=src
inc                    :=$(base)/inc

universal              :=$(inc)/universal.h
interface              :=$(inc)/data_structure_interface.h
common                 :=$(base)/common/common_declaration.h
type                   :=$(inc)/types.h
data_structure         :=$(inc)/data_structure_types.h

script                 :=script
script_module_decl     :=$(script)/produce_module_declaration_h.pl
script_universal       :=$(script)/produce_universal_h.pl
script_interface       :=$(script)/produce_data_structure_interface_h.pl

vpath %.h $(inc)

## first target should be in front of sub-makefile
all:

include src/makefile.mk
include src/common/makefile.mk
include src/graph/makefile.mk
include src/hash/makefile.mk
include src/heap/makefile.mk
include src/linked_list/makefile.mk
include src/queue/makefile.mk
include src/set/makefile.mk
include src/sort/makefile.mk
include src/stack/makefile.mk
include src/test/makefile.mk
include src/tree/makefile.mk

-include $(dep)

CF_DEBUG               :=-DDEBUG -g
CF_RELEASE             :=-O3
CF_COVERAGE            :=--coverage

CFLAG                  +=$(addprefix -I,$(inc))
CFLAG                  +=-DX86_64 -DLIBC
CFLAG                  +=$(if $(RELEASE),$(CF_RELEASE),$(CF_DEBUG))

ifdef COVERAGE
    CFLAG              +=$(CF_COVERAGE)
endif

LFLAG                  +=$(if $(RELEASE),$(CF_RELEASE),$(CF_DEBUG))
LFLAG                  +=$(if $(COVERAGE),$(CF_COVERAGE),)
SLFLAG                 +=$(if $(RELEASE),$(CF_RELEASE),$(CF_DEBUG))

## COVERAGE build ##

.PHONY:all help clean

TARGET_ELF             :=$(addprefix $(out)/, ds.elf)
TARGET_A               :=$(addprefix $(out)/, libds.a)
TARGET_SO              :=$(addprefix $(out)/, libds.so)
TARGET_DEP             :=$(decl) $(universal) $(interface)

all:$(out) $(TARGET_DEP) $(TARGET_ELF) $(TARGET_A) $(TARGET_SO)

$(out):
	@echo "    MakeDir  $@"
	$(MKDIR) $@

## declaration header files ##
$(decl):%_declaration.h:%.c
	$(PERL) $(script_module_decl) $(dir $<)

## specific header files  ##
$(universal):$(common)
	$(PERL) $(script_universal) $@ $<
$(interface):$(type) $(data_structure) $(decl_partial)
	$(PERL) $(script_interface) $(inc) $@ $(decl_partial)

## depend target ##
$(dep):%.d:%.c
	@echo "    Depend   $(notdir $@)"
	$(CC) -M -MT '$(basename $<).o $(basename $<).d' $(CFLAG) $< -o $@
	$(if $(filter %main.c, $<),,$(update_decl_depend))

## .elf target ##
$(TARGET_ELF):$(obj)
	@echo "    Link     $@"
	$(CC) $(LFLAG) $^ -o $@ $(lib)

## .a target ##
$(TARGET_A):$(obj_partial)
	@echo "    Archive  $@"
	@$(AR) $(AFLAG) $@ $^

## .so target ##
$(TARGET_SO):$(obj_partial)
	@echo "    Shared   $@"
	$(CC) $(SLFLAG) $^ -o $@ $(lib)

## object ##
$(obj):%.o:%.c
	@echo "    Compile  $(notdir $<)"
	$(CC) $(CFLAG) $< -o $@

clean:
	@echo "    Clean    Object"
	@$(RM) $(obj)
	@echo "    Clean    Depend"
	@$(RM) $(dep)

help:
	@echo
	@echo "  make            :Default debug build"
	@echo "  make RELEASE=1  :Release build"
	@echo "  make V=1        :Verbose build"
	@echo "  make COVERAGE=1 :Coverage build"
	@echo

## define list ##
define update_decl_depend
	@echo "$(basename $<)_declaration.h: $(shell find $(dir $<)impl | grep "\.c$$")" >> $@
endef

