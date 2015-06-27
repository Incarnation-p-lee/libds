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
              "$srcdir/queue/queue.h",
              "$srcdir/stack/stack.h",
              "$srcdir/tree/tree.h",
              "$srcdir/hash/hash.h",
              "$srcdir/heap/heap.h",
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
    print OUT "\n/* BEGIN of $fname */\n";
    while (<EXPORT>) {
        my $line = $_;
        if (/static/) { # filter static function
            next if $line =~ /\);$/;
        } elsif (/^struct\s/) {
            unless (/\{$/) {
                $line = 'extern ' . $_;
            }
        } elsif (/^void\s/) {
            $line = 'extern ' . $_;
        } elsif (/^[us]int\d{2}\s/) {
            $line = 'extern ' . $_;
        } elsif (/^bool\s/) {
            $line = 'extern ' . $_;
        } elsif (/^FILE/) {
            next;
        } elsif (/^extern/) {
            next;
        }
        print OUT $line;
    }

    print OUT "/* END of $fname */\n";
    close EXPORT;
}

print OUT "#endif /* END OF FILE */";
close OUT;
