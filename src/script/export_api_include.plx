#!/usr/bin/perl
use strict;
use 5.010;

my $base = ".";
my $incdir = "$base/src/inc";

my @export = ("$incdir/types.h",
              "$incdir/data_structure_types.h",
              "$incdir/log.h",
              "$incdir/tree.h",
              "$incdir/defines.h",
              "$incdir/linked_list.h",
              "$incdir/queue.h",
              "$incdir/stack.h");
my $out = "$base/src/inc/ds.h";

open OUT, '>', $out or
  die "$!";

print OUT "#ifndef HAVE_DATA_STRUCTURE_INCLUDE_H\n";
print OUT "#define HAVE_DATA_STRUCTURE_INCLUDE_H\n";

foreach (@export) {
    open EXPORT, '<', $_ or
        die "$!";
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
