#!/usr/bin/perl
use strict;
use warnings;
use 5.010;
use lib './script';
use scan_source_file;

my $debug = shift @ARGV;
my $srcdir = "$ENV{'PWD'}/src";
my @module = ("$srcdir/linked_list",
              "$srcdir/hash",
              "$srcdir/queue",
              "$srcdir/stack",
              "$srcdir/heap",
              "$srcdir/test",
              "$srcdir/tree",
              "$srcdir/sort",
              "$srcdir/test/unit_test",
              "$srcdir/test/performance_test",
              "$srcdir/common",);

say "produce module_declaration.h";

foreach (@module) {
    my $module = $1 if /\/(\w+)$/;
    my $file_name = "$_/$module" . "_declaration.h";
    my $implement = "$_/impl";
    my @collection;
    my @declartion;

    open DECLARATION, '>', $file_name or die "Failed to open file $file_name, $!";
    printf DECLARATION "#ifndef HAVE_DEFINED_$module" . "_H\n";
    printf DECLARATION "#define HAVE_DEFINED_$module" . "_H\n\n";

    opendir MODULE, $implement or die "Failed to open directory $implement, $!";

    while (readdir(MODULE)) {
        # All debug files are in the form of xxx_debug.c ##
        next if /_debug/ and ($debug eq "No");
        if (/\w+\.c$/) {
            @declartion = scan_source_file_implement("$implement/$_");
            push @collection, @declartion;
        }
    }

    @collection = sort @collection;
    foreach (@collection) {
        printf DECLARATION $_;
    }

    closedir MODULE;

    printf DECLARATION "\n#endif\n\n";
    close DECLARATION;
}

