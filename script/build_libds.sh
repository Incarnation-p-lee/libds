#!/bin/sh
## addition cc and ld config ##
cc_config="-fPIC"
ld_config="-Wl,--stats"
ld_library=
debug_mode="Yes"
target=

if [ $# == 0 ]
then
    cat << EOF
Build Script Usage:
    sh src/script/build_libds.sh DEBUG/RELEASE
                                 X86_64/X86_32
                                 LIBC/KERNEL
                                 ELF/OBJ/DYN
                                 PROFILE       -optional
                                 COVERAGE      -optional
EOF
    exit 1
fi

base=$(pwd)
src_dir=$base/src
output_dir=$base/output
obj_dir=$output_dir/obj
bin_dir=$output_dir/bin
inc_dir=$output_dir/inc
arg_list=$@
arg_tmp=
binary_list="ELF OBJ DYN"

#######################
## parameters handle ##
#######################
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
            debug_mode="Yes"
            cc_config="$cc_config -g3 -DDEBUG" ;;
        "RELEASE")
            debug_mode="No"
            cc_config="$cc_config -o3 -ofast"
            ld_config="$ld_config -Wl,-O3" ;;
        "LIBC")
            cc_config="$cc_config -DLIBC"
            ld_library="-lc -lm" ;;
        "KERNEL")
            cc_config="$cc_config -DKERNEL -nostdlib -nostdinc -fno-builtin" ;;
        "ALL")
            target=ALL ;;
        "ELF")
            target=elf ;;
        "OBJ")
            target=obj ;;
        "DYN")
            target=dyn
            ld_config="$ld_config -shared -fPIC" ;;
        "COVERAGE")
            cc_config="$cc_config --coverage"
            ld_config="$ld_config --coverage" ;;
    esac
done

########################
## Check if build ALL ##
#######################
if [ "$target" == "ALL" ]
then
    arg_list=${arg_list// ALL/}

    for binary in $binary_list
    do
        arg_tmp="$arg_list $binary"
        echo && echo "sh $0 $arg_tmp"
        sh $0 $arg_tmp
    done

    exit 0
fi

#############################
## create output directory ##
#############################
if [ -d $obj_dir ]
then
    rm -rf $obj_dir
    echo "Remove last build directory $obj_dir"
fi
mkdir -p $obj_dir

###########################################
## update some header files and makefile ##
###########################################
perl script/produce_module_declaration_h.pl $debug_mode
perl script/produce_universal_h.pl
perl script/produce_data_structure_interface_h.pl $inc_dir
perl script/produce_compile_makefile.pl $src_dir

####################################
## compiling object file function ##
####################################
function obj_compile() {
    make "cc_config=$cc_config" -f $1/Makefile
    if [ "$?" != 0 ]
    then
        exit 3
    else
        mv *.o $obj_dir
    fi
}

###################################
## compile main.o for elf target ##
###################################
if [ "$target" == "elf" ]
then
    obj_compile $src_dir
fi

########################################
## compiling all other subdir .o file ##
########################################
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

###############################
## generate linking Makefile ##
###############################
perl script/produce_link_makefile.pl $obj_dir $bin_dir

#######################
## link final target ##
#######################
cp $src_dir/Makefile.in $obj_dir && cd $obj_dir
make "ld_config=$ld_config" "ld_library=$ld_library" $target

if [ "$?" != 0 ]
then
    exit 4
else
    cd - > /dev/null
fi

#################################
## Update tags and cleanup log ##
#################################
ctags -R src && rm -vf libds.log

########################################
## End of build script execution flow ##
########################################

