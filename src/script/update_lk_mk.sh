#!/bin/sh

objdir=obj_out
mkfile=Makefile
srcdir=src
cd $objdir > /dev/null
static=0

for argv in "$@"
do
  case $argv in
    "static=1")
    static=1
    ;;
  esac
done

if [ "$static" == "1" ]
then
  objfile="test.o main.o"
  static_lib="libds.a"
else
  objfile=`ls *.o`
fi

cat << EOF > $mkfile
include ../$srcdir/base.Makefile

.phony:lib stlib dylib

\$(TARGET):`echo $objfile`
	\$(CC) \$(LFLAG) -o \$@ \$^ $static_lib \$(EXTLIB)
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
