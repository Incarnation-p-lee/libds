#!/usr/bin/perl
use strict;
use warnings;
use 5.010;
use lib './script';
use scan_source_file;

my $header = shift @ARGV;
my $source = shift @ARGV;

my @result = &scan_header_file_externals($source);
my $basename = $1 if $header =~ /(\w+\.h)/;

say "    Generate $basename";

open UNIVERSAL, '>', $header or die "Failed to locate $header, $!\n";

    printf UNIVERSAL "#ifndef HAVE_DEFINED_UNIVERSAL_H\n";
    printf UNIVERSAL "#define HAVE_DEFINED_UNIVERSAL_H\n\n";
    printf UNIVERSAL "// Automaticaly generated by $0.\n\n";

    foreach(@result) {
        printf UNIVERSAL "extern $_";
    }

    printf UNIVERSAL "\n#endif\n\n";

close UNIVERSAL;

