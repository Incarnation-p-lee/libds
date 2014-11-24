#!/bin/sh

argv_cfg=
argv_lnk=
argv_lib=
lib_build=0
root_dir=`pwd | xargs basename`

if [ "$root_dir" != "libds" ]
then
  echo "Please execute build script under root dir: libds/"
  echo "Example:"
  echo "    sh src/script/build.sh DEBUG=1 LIB=1"
  exit 1
fi

function print_help() {
  cat << EOF
Build Script Usage:
    sh src/script/build.sh DEBUG=0/1
                           PROFILE=0/1
                           LIB=0/1
                           CODE_COVERAGE=0/1
                           X86_64=0/1
                           STATIC=0/1
EOF
  exit 2
}

platform=0
static=0

for argv in "$@"
do
  case $argv in
    "X86_64=0")
      argv_cfg="$argv_cfg -m32 -DX86"
      argv_lnk="$argv_lnk -m32"
      platform="1"
    ;;
    "X86_64=1")
      argv_cfg="$argv_cfg -m64 -DX86_64"
      argv_lnk="$argv_lnk -m64"
      platform="1"
    ;;
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
    "LIB=1")
      lib_build=1
    ;;
    "LIB=0")
      lib_build=0
    ;;
    "-h")
      print_help
    ;;
    "--help")
      print_help
    ;;
    "STATIC=1")
      static=1
    ;;
  esac
done

# if not specific platform, use X86_64 by default
if [ "$platform" != "1" ]
then
  argv_cfg="$argv_cfg -m64 -DX86_64"
  argv_lnk="$argv_lnk -m64"
fi

# create output directory
objdir=obj_out
if [ -d $objdir ]
then
  rm -rfv $objdir
fi
mkdir -vp $objdir
mkdir -vp $objdir/out/

perl src/script/export_api_include.plx
cp src/inc/ds.h $objdir/out/

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
    "src/lib/")
    continue
  ;;
  esac

  compile_obj $dir
done

# compiling main.o
compile_obj "src/"

# generate makefile for obj_out
sh src/script/update_lk_mk.sh "static=$static"
# link to elf
cd $objdir > /dev/null

if [ "$lib_build" -eq "1" ]
then
  make "lib"
  cp -v ./out/libds.so ../src/lib
  cp -v ./out/libds.a ../src/lib
  if [ "$static" == "1" ]
  then
    cp -v ./out/libds.a ./
  fi
fi

make "ARGV_LNK=$argv_lnk" "ARGV_LIB=$argv_lib"

cd - > /dev/null
