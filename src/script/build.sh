#!/bin/sh

argv_cfg=
argv_lnk=

for argv in "$@"
do
  case $argv in
    "DEBUG=1")
      argv_cfg="$argv_cfg -g -DDEBUG"
    ;;
    "DEBUG=0")
      argv_cfg="$argv_cfg -o2"
    ;;
    "CODE_COVERAGE=1")
      argv_cfg="$argv_cfg -fprofile-arcs -ftest-coverage"
      argv_lnk="$argv_lnk -fprofile-arcs -ftest-coverage"
    ;;
    "PROFILE=1")
      argv_lnk="$argv_lnk -pg"
      argv_cfg="$argv_cfg -pg"
    ;;
    "CODE_COVERAGE=0")
    ;;
    "PROFILE=0")
    ;;
  esac
done


objdir=obj_out

if [ -d $objdir ]
then
  rm -rfv $objdir
fi

mkdir -vp $objdir
mkdir -vp $objdir/out/

function compile_obj() {
  cd $1 > /dev/null
  make "ARGV_CFG=$argv_cfg"
  cd - > /dev/null
  mv -v $1*.o $objdir
}

# compiling .o files for all subdir
for dir in `ls -d src/*/`
do
  case $dir in
    "src/script/")
    continue
  ;;
    "src/inc/")
    continue
  ;;
  esac

  compile_obj $dir
done

# compiling main.o
compile_obj "src/"

# generate makefile for obj_out
sh src/script/update_lk_mk.sh
# link to elf
cd $objdir > /dev/null
make "ARGV_LNK=$argv_lnk"
cd - > /dev/null
