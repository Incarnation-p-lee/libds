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
	@echo "Build Executable .................................... [32mOK[0m."

lib:\$(STLIB) \$(DYLIB)
	@echo "Build Library ....................................... [32mOK[0m."
	@date

\$(STLIB):\$(LIBOBJ)
	\$(AR) \$(AFLAG) -o \$@ \$^
	@mv -v \$@ ./out

\$(DYLIB):\$(LIBOBJ)
	\$(CC) \$(DFLAG) -o \$@ \$^
	@mv -v \$@ ./out

EOF
