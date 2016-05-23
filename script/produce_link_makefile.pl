#!/usr/bin/perl
use strict;
use 5.010;

my $output = "output";
my $obj_list = "";
my $obj_part = "";

die "Failed to find output directory, $output." unless -d -e $output;

## Collecting all objective files in output ##
opendir OUTPUT, $output or
    die "Failed to open output directory $output, $?\n";

while(readdir(OUTPUT)) {
    if (/(\w+)\.o/) {
        $obj_list = "$_ $obj_list";
        $obj_part = "$_ $obj_part" unless /(test|main)/;
    }
}

chop $obj_list;
closedir OUTPUT;

## Generate link Makefile in output ##
open MAKEFILE, '>', "$output/Makefile" or
    die "Failed to create makefile, $?\n";

printf MAKEFILE "include Makefile.in\n";
printf MAKEFILE 'all:$(ELF_TARGET) $(OBJ_TARGET) $(DYN_TARGET)' ."\n\n";
printf MAKEFILE "\$(ELF_TARGET):$obj_list\n";
printf MAKEFILE "\t" . '$(LD) $(LFLAG) -o $@ $?' . "\n\n";
printf MAKEFILE "\$(DYN_TARGET):$obj_part\n";
printf MAKEFILE "\t" . '$(LD) $(LFLAG) -o $@ $?' . "\n\n";
printf MAKEFILE "\$(OBJ_TARGET):$obj_part\n";
printf MAKEFILE "\t" . '$(AR) $(AFLAG) -o $@ $?' . "\n\n";

close MAKEFILE;

