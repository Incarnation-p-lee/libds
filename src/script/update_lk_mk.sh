#!/bin/sh

objdir=obj_out
mkfile=Makefile
srcdir=src
cd $objdir > /dev/null
static=""
depend_lib=""


for argv in "$@"
do
  case $argv in
    "static=1")
    static=1
    ;;
    "static=0")
    static=0
    ;;
  esac
done

if [ "$static" == "1" ]
then
  # static linked library libds.a
  objfile="test.o main.o"
  depend_lib="libds.a"
elif [ "$static" == "0" ]
then
  # dynamic linked library libds.so
  objfile="test.o main.o"
  depend_lib="-lds"
else
  objfile=`ls *.o`
fi

cat << EOF > $mkfile
include ../$srcdir/base.Makefile

.phony:lib stlib dylib

\$(TARGET):`echo $objfile`
	\$(CC) \$(LFLAG) -o \$@ \$^ $depend_lib \$(EXTLIB)
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
