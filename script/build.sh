#!/bin/sh
## addition cc and ld config ##
cc_config="-fPIC"
ld_config="-fPIC"
binary_config="ALL"

if [ $# == 0 ]
then
    cat << EOF
Build Script Usage:
    sh src/script/build.sh DEBUG/RELEASE
                           X86_64/X86_32
                           LIBC
                           PROFILE         -optional
                           CODE_COVERAGE   -optional
                           ALL/ELF/OBJ/DYN -optional
EOF
    exit 1
fi

base=$(pwd)
src_dir=$base/src
objdir=$base/output
bindir=$objdir/out

## parameters handle ##
for pm in "$@"
do
    case $pm in
        "X86_64")
            cc_config="$cc_config -m64 -DX86_64"
            ld_config="$ld_config -m elf_x86_64" ;;
        "X86_32")
            cc_config="$cc_config -m32 -DX86_32 -fno-stack-protector"
            ld_config="$ld_config -m elf_i386" ;;
        "DEBUG")
            cc_config="$cc_config -g3 -DDEBUG" ;;
        "RELEASE")
            cc_config="$cc_config -o3 -ofast -DNDEBUG" ;;
        "LIBC")
            cc_config="$cc_config -DLIBC" ;;
        "ELF")
            binary_config="ELF" ;;
        "OBJ")
            binary_config="OBJ" ;;
        "DYN")
            binary_config="DYN" ;;
    esac
done

## create output directory ##
if [ -d $objdir ]
then
    rm -rf $objdir
fi
mkdir -p $bindir

## update head file ds.h, makefile and declarations ##
perl script/export_api_include.plx
cp src/inc/ds.h $bindir
perl script/produce_compile_makefile.pl $src_dir
perl script/declaration_generate.plx $debug

## compiling object file function ##
function obj_compile() {
    make -C $1 "cc_config=$cc_config"
    if [ "$?" != 0 ]
    then
        exit 3
    else
        mv $1/*.o $objdir
    fi
}

## compile main.o ##
obj_compile $src_dir

## compiling all other subdir .o file##
for dir in `ls -d src/*/`
do
    case $dir in
        "src/inc/") continue ;;
    esac
    obj_compile $dir
done

## generate linking Makefile ##
perl script/produce_link_makefile.pl

## link final target ##
cp $src_dir/Makefile.in $objdir && cd $objdir
make "ld_config=$ld_config"
if [ "$?" != 0 ]
then
    exit 4
else
    mv *.so *.elf *.a $bindir && cd - > /dev/null
fi

## Update tags and cleanup log ##
ctags -R src && rm -vf libds.log

## End of build script execution flow ##

