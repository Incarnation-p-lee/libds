#!/usr/bin/perl
use strict;
use 5.010;

my $base = ".";
my $srcdir = "$base/src";
my @declarnations;
my $debug_version;
my @modules = ("$srcdir/linked_list",
               "$srcdir/hash",
               "$srcdir/queue",
               "$srcdir/stack",
               "$srcdir/heap",
               "$srcdir/test",
               "$srcdir/tree",
               "$srcdir/test/unit_test",
               "$srcdir/test/performance_test",
               "$srcdir/log",
               "$srcdir/common",
           );

$debug_version = shift @ARGV;

foreach (@modules) {
    my $entry = $_;
    &module_traversal($entry);
    &module_header_file_generate($entry);
}

sub module_header_file_generate () {
    my $md_name = shift @_;
    my @sorted = sort @declarnations;
    my $basename = $1 if $md_name =~ /\/(\w+)$/;
    my $dec_fname = "$md_name/$basename" . "_declaration.h";
    my $macro = uc($basename . "_declaration_h");

    open DECL, '>', $dec_fname or die "$! $dec_fname";
    print DECL "#ifndef $macro\n";
    print DECL "#define $macro\n\n";

    foreach (@sorted) {
        print DECL "$_\n";
    }

    print DECL "\n#endif\n";
    close DECL;

    @declarnations = undef;
}


sub module_traversal() {
    my $basedir = shift @_;

    opendir MD, $basedir or die "$! $basedir.";

    while (readdir(MD)) {
        next if /unit_test_maximal_heap/;
        next if /unit_test_min_max_heap/;
        next if /performance_test_maximal_heap/;
        next if /performance_test_min_max_heap/;

        if ("$_" eq "." or "$_" eq ".." or /^\./) {
            next;
        } elsif (-d "$basedir/$_") {
            &module_traversal("$basedir/$_") if /impl/;
        } else {
            my $fname = "$basedir/$_";
            next if "$debug_version" eq "0" and /debug/;
            &file_scan($fname) if $fname =~ /impl/;
        }
    }   

    closedir MD;
}

sub file_scan() {
    my $filename = shift @_;
    my $body = 1;
    my $head;

    print "Scanning source file $filename ";

    open IMP, '<', $filename or die "$! $filename.";

    while (<IMP>) {
        chomp;
        next if /^$/;
        next if /:$/;
        next if /^UT_/;
        next if /^PT_/;

        if (/^\w/) {
            $body = 0;
        } elsif (/^{/) {
            $body = 1;
        }

        if ("$body" eq "0") {
            my $real = $_;
            $real = $1 if (/^\s+(.*)/);
            $head = $head . "$real ";
        } elsif ($head){
            print ".";
            $head =~ s/\s$/;/g;
            unshift @declarnations, $head;
            $head = undef;
        }
    }

    print "\n";

    close IMP;
}

