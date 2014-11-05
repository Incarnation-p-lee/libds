#!/bin/sh

objdir=obj_out
mkfile=Makefile
srcdir=src
cd $objdir > /dev/null
objfile=`ls *.o`
cat << EOF > $mkfile
include ../$srcdir/base.Makefile

.phony:lib stlib dylib

\$(TARGET):`echo $objfile`
	\$(CC) \$(LFLAG) -o \$@ \$^ \$(EXTLIB)
	@mv -v \$@ ./out

lib:\$(LIBOBJ)
	make stlib
	make dylib

stlib:\$(LIBOBJ)
	\$(AR) \$(AFLAG) -o \$(STLIB) \$(LIBOBJ)
	@mv -v \$(STLIB) ./out

dylib:\$(LIBOBJ)
	\$(CC) \$(DFLAG) -o \$(DYLIB) \$(LIBOBJ)
	@mv -v \$(DYLIB) ./out

EOF
