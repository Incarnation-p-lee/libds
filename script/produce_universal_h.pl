#!/usr/bin/perl
use strict;
use warnings;
use 5.010;
use lib './script';
use scan_source_file;

my $header = "$ENV{'PWD'}/src/inc/universal.h";
my $source = "$ENV{'PWD'}/src/common/common_declaration.h";
my @result = &scan_header_file_externals($source);

say "produce universal.h";

open UNIVERSAL, '>', $header or die "Failed to locate $header, $!\n";

    printf UNIVERSAL "#ifndef HAVE_DEFINED_UNIVERSAL_H\n";
    printf UNIVERSAL "#define HAVE_DEFINED_UNIVERSAL_H\n\n";

    foreach(@result) {
        printf UNIVERSAL "extern $_";
    }

    printf UNIVERSAL "\n#endif\n\n";

close UNIVERSAL;

