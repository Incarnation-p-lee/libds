#!/usr/bin/perl
use strict;
use warnings;
use 5.010;
use lib './script';
use scan_source_file;

my $header = "$ENV{'PWD'}/src/inc/data_structure_interface.h";
my $srcdir = "$ENV{'PWD'}/src";
my $inc_dir = shift @ARGV;

say "Produce data_structure_interface.h";

#######################################
## Create data_structure_interface.h ##
#######################################
open INTERFACE, '>', $header or die "Failed to locate $header, $!\n";

printf INTERFACE "#ifndef HAVE_DEFINED_DATA_STRUCTURE_INTERFACE_H\n";
printf INTERFACE "#define HAVE_DEFINED_DATA_STRUCTURE_INTERFACE_H\n\n";
printf INTERFACE "// Automaticaly generated by $0.\n\n";

##################
## Scan typedef ##
##################
my $source = "$srcdir/inc/types.h";
my @typedef = scan_header_file_typedefs($source);
foreach (@typedef) {
    printf INTERFACE "$_";
}
printf INTERFACE "\n";

#############################
# enum/structure in types.h #
#############################
my @structure = scan_header_file_structure($source);
foreach (@structure) {
    printf INTERFACE "$_";
}
printf INTERFACE "\n";

#####################
## Scan definition ##
#####################
$source = "$srcdir/inc/data_structure_types.h";
my @definition = scan_header_file_definition($source);
foreach (@definition) {
    printf INTERFACE "$_";
}
printf INTERFACE "\n";

####################
## Scan structure ##
####################
@structure = scan_header_file_structure($source);
foreach (@structure) {
    printf INTERFACE "$_";
}
printf INTERFACE "\n";

###############################
## Scan function declaration ##
###############################
my @delaration = ("$srcdir/common/common_declaration.h",
                  "$srcdir/linked_list/linked_list_declaration.h",
                  "$srcdir/queue/queue_declaration.h",
                  "$srcdir/stack/stack_declaration.h",
                  "$srcdir/tree/tree_declaration.h",
                  "$srcdir/hash/hash_declaration.h",
                  "$srcdir/heap/heap_declaration.h",
                  "$srcdir/sort/sort_declaration.h",
                  "$srcdir/set/set_declaration.h",
);

foreach (@delaration) {
    my @external = scan_header_file_externals($_);
    foreach (@external) {
        printf INTERFACE "extern $_";
    }
    printf INTERFACE "\n";
}

printf INTERFACE "\n#endif\n\n";

close INTERFACE;

system("cp -v $header $inc_dir");

