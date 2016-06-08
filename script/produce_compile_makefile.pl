#!/usr/bin/perl
use strict;
use warnings;
use 5.010;

my $work_dir = shift @ARGV;
my $current_dir = "$ENV{'PWD'}";
my $source_dir = "$current_dir/src";
my $include_dir = "$source_dir/inc";

say "produce compile Makefile";

if ($work_dir eq "") {
    say "Please specify the work directory for makefile producing";
    exit 1;
} else {
    $work_dir = $1 if $work_dir =~ /(\w+)\/?$/;
    &create_compile_makefile("$work_dir") if -e "$work_dir/main.c";
    &visit_workspace($work_dir);
}

sub visit_workspace {
    my $base = shift @_;

    if ( -e -d $base) {
        opendir WORKSPACE, $base or
            die "Failed to open work directory $base, $?\n";

        my @work_list = readdir(WORKSPACE);

        foreach my $entry (@work_list) {
            next if $entry =~ /^\.$/;
            next if $entry =~ /^\.\.$/;
            next if $entry =~ /^inc$/;

            my $sub_dir = "$base/$entry";
            if (-e -d $sub_dir) {
                &create_compile_makefile($sub_dir);
                #
                # No recursive here
                # &visit_workspace($sub_dir)
            }
        }

        closedir WORKSPACE;
    }
}

sub create_compile_makefile {
    my $dir;
    my $file;

    $dir = shift @_;
    $dir =~ /\w+/ or
        die "Script DO NOT know how to make one makefile without a module name.";

    $file = $1 if $dir =~ /\/?(\w+)$/;

    ## handle main.c Makefile ##
    $file = "main" if -e "$dir/main.c";

    open MAKEFILE, '>', "$dir/Makefile" or
        die "Failed to create makefile, $?\n";

    printf MAKEFILE "include $source_dir/Makefile.in\n";
    printf MAKEFILE "CFLAG += -I$include_dir\n\n";
    printf MAKEFILE "all:$file.o\n\n";
    printf MAKEFILE "$file.o:$current_dir/$dir/$file.c\n";
    printf MAKEFILE "\t" . '$(CC) $(CFLAG) -o $@ $<' . "\n\n";

    close MAKEFILE;
}

