#!/usr/bin/perl
use strict;
use warnings;
use feature qw(say);
use lib './script';
use scan_source_file;

my $module_dir = shift @ARGV;
my $module = $1 if $module_dir =~ /\/(\w+)\/$/;
my $filename;
my $basename;
my $implement;
my @collection;
my @collection_debug;
my @declartion;

exit 0 if $module =~ /main\.c$/;

$filename = "$module_dir/$module" . "_declaration.h";
$basename = $1 if $filename =~ /(\w+\.h)/;
$implement = "$module_dir/impl";

say "    Generate $basename";

open DECLARATION, '>', $filename or die "Failed to open file $filename, $!";
    printf DECLARATION "#ifndef HAVE_DEFINED_$module" . "_H\n";
    printf DECLARATION "#define HAVE_DEFINED_$module" . "_H\n\n";
    printf DECLARATION "// Automaticaly generated by $0.\n\n";

    opendir MODULE, $implement or die "Failed to open directory $implement, $!";

    while (readdir(MODULE)) {
        # All debug files are in the form of xxx_debug.c ##
        if (/_debug/ and /\w+\.c$/) {
            @declartion = scan_source_file_implement("$implement/$_");
            push @collection_debug, @declartion;
        } elsif (/\w+\.c$/) {
            @declartion = scan_source_file_implement("$implement/$_");
            push @collection, @declartion;
        }
    }

    @collection_debug = sort @collection_debug;
    printf DECLARATION "#if defined DEBUG\n\n";
    foreach (@collection_debug) {
        printf DECLARATION $_;
    }
    printf DECLARATION "\n#endif\n\n";

    @collection = sort @collection;
    foreach (@collection) {
        printf DECLARATION $_;
    }

    closedir MODULE;

    printf DECLARATION "\n#endif\n\n";
close DECLARATION;

