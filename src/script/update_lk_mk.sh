#!/bin/sh

objdir=obj_out
mkfile=Makefile
srcdir=src
cd $objdir > /dev/null
objfile=`ls *.o`
cat << EOF > $mkfile
include ../$srcdir/base.Makefile

\$(TARGET):`echo $objfile`
	\$(CC) \$(LFLAG) -o \$@ \$^ \$(EXTLIB)
	mv \$@ ./out
EOF
