#!/usr/bin/perl
use strict;
use 5.010;

my $work_dir = shift @ARGV;
my $include_dir = "$ENV{'PWD'}/src/inc";

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
            chomp;
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
    my $make_in;

    $dir = shift @_;
    $dir =~ /\w+/ or
        die "Script DO NOT know how to make one makefile without a module name.";

    $make_in = ".";
    $make_in = $1 if $dir =~ /\/?\w+\/(.+)/;
    $make_in =~ s/\w+/../g;
    $file = $1 if $dir =~ /\/?(\w+)$/;

    ## handle main.c Makefile ##
    $file = "main" if -e "$dir/main.c";

    open MAKEFILE, '>', "$dir/Makefile" or
        die "Failed to create makefile, $?\n";

    printf MAKEFILE "include $make_in/Makefile.in\n";
    printf MAKEFILE "CFLAG += -I$include_dir\n\n";
    printf MAKEFILE "TARGET = $file.o\n";
    printf MAKEFILE 'all:$(TARGET)' ."\n\n";
    printf MAKEFILE ".c.o:\n";
    printf MAKEFILE "\t" . '$(CC) $(CFLAG) -o $@ $<' . "\n";

    close MAKEFILE;
}

