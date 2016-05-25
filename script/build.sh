#!/bin/sh
## addition cc and ld config ##
cc_config="-fPIC"
ld_config="-Wl,--stats"
ld_library=
debug_mode=
target=

if [ $# == 0 ]
then
    cat << EOF
Build Script Usage:
    sh src/script/build.sh DEBUG/RELEASE
                           X86_64/X86_32
                           LIBC/KERNEL
                           ELF/OBJ/DYN
                           PROFILE         -optional
                           CODE_COVERAGE   -optional
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
            ld_config="$ld_config -m64" ;;
        "X86_32")
            cc_config="$cc_config -m32 -DX86_32 -fno-stack-protector"
            ld_config="$ld_config -m32" ;;
        "DEBUG")
            debug_mode=1
            cc_config="$cc_config -g3 -DDEBUG" ;;
        "RELEASE")
            debug_mode=0
            cc_config="$cc_config -o3 -ofast -DNDEBUG"
            ld_config="$ld_config -Wl,-O3" ;;
        "LIBC")
            cc_config="$cc_config -DLIBC"
            ld_library="-lc -lm" ;;
        "KERNEL")
            cc_config="$cc_config -DKERNEL -nostdlib -nostdinc -fno-builtin" ;;
        "ELF")
            target=elf ;;
        "OBJ")
            target=obj ;;
        "DYN")
            target=dyn
            ld_config="$ld_config -shared -fPIC" ;;
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
perl script/declaration_generate.plx $debug_mode

## compiling object file function ##
function obj_compile() {
    make "cc_config=$cc_config" -f $1/Makefile
    if [ "$?" != 0 ]
    then
        exit 3
    else
        mv *.o $objdir
    fi
}

## compile main.o for elf target ##
if [ "$target" == "elf" ]
then
    obj_compile $src_dir
fi

## compiling all other subdir .o file ##
for dir in `ls -d src/*/`
do
    if [ "$target" != "elf" ] && [ "$dir" == "src/test/" ]
    then
        continue
    fi
    case $dir in
        "src/inc/") continue ;;
    esac
    obj_compile $dir
done

## generate linking Makefile ##
perl script/produce_link_makefile.pl

## link final target ##
cp $src_dir/Makefile.in $objdir && cd $objdir
make "ld_config=$ld_config" "ld_library=$ld_library" $target

if [ "$?" != 0 ]
then
    exit 4
else
    cd - > /dev/null
fi

## Update tags and cleanup log ##
ctags -R src && rm -vf libds.log

## End of build script execution flow ##

