#!/usr/bin/perl
use strict;
use 5.010;

my $base = ".";
my $incdir = "$base/src/inc";
my $srcdir = "$base/src";

my @export = ("$incdir/types.h",
              "$incdir/data_structure_types.h",
              "$incdir/data_structure_defines.h",
              "$incdir/defines.h",
              # data structure modual
              "$srcdir/linked_list/linked_list.h",
              "$srcdir/linked_list/linked_list_declaration.h",
              "$srcdir/queue/queue.h",
              "$srcdir/queue/queue_declaration.h",
              "$srcdir/stack/stack.h",
              "$srcdir/stack/stack_declaration.h",
              "$srcdir/tree/tree.h",
              "$srcdir/tree/tree_declaration.h",
              "$srcdir/hash/hash.h",
              "$srcdir/hash/hash_declaration.h",
              "$srcdir/heap/heap.h",
              "$srcdir/heap/heap_declaration.h",
              "$srcdir/sort/sort.h",
              "$srcdir/sort/sort_declaration.h",
              # log
              "$srcdir/log/log.h",);
my $out = "$base/src/inc/ds.h";

open OUT, '>', $out or
  die "$!";

print OUT "#ifndef HAVE_DATA_STRUCTURE_INCLUDE_H\n";
print OUT "#define HAVE_DATA_STRUCTURE_INCLUDE_H\n";

foreach (@export) {
    open EXPORT, '<', $_ or
        die "$! $_.";
    my $fname = $_;
    my $debug = 0;
    print OUT "\n/* BEGIN of $fname */\n";
    while (<EXPORT>) {
        my $line = $_;

        if ("$debug" eq "1") {
            $debug -= 1 if /endif/;
            next;
        } elsif (/FILE/) {
            next;
        } elsif (/static/) { # filter static function
            next if $line =~ /\);$/;
        } elsif (/^struct\s/) {
            $line = 'extern ' . $_ unless /\{$/;
        } elsif (/^void\s/) {
            $line = 'extern ' . $_;
        } elsif (/^[us]int\d{2}\s/) {
            $line = 'extern ' . $_;
        } elsif (/^bool\s/) {
            $line = 'extern ' . $_;
        } elsif (/^extern/) {
            next;
        } elsif (/DEBUG/ && /def/) {
            $debug += 1;
            next;
        }
        print OUT $line;
    }

    print OUT "/* END of $fname */\n";
    close EXPORT;
}

print OUT "#endif /* END OF FILE */";
close OUT;
