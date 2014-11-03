#!/usr/bin/perl
use strict;
use 5.010;

my $base = ".";
my $incdir = "$base/src/inc";

my @export = ("$incdir/data_structure_types.h",
              "$incdir/log.h",
              "$incdir/types.h");
my $out = "$base/obj_out/out/ds.h";

foreach(@export) {
}
