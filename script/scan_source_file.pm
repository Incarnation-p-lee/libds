#!/usr/bin/perl
use strict;
use warnings;
use 5.010;

## scan given source file and filter out kinds of contents ##

sub scan_header_file_externals {
    my @result;
    my $file_name;

    $file_name = shift @_;
    open SRC_FILE, '<', $file_name or die "Failed to open file $file_name, $!";

    while (<SRC_FILE>) {
        chomp $_;
        if (/^void/ or /^bool/ or /^[su]int(32|64|16|8)/ or /^struct (\w)+ /) {
            push @result, "$_\n" if /;$/;
        }
    }
    
    close SRC_FILE;
    @result = sort @result;
}

sub scan_header_file_typedefs {
    my @result;
    my $last;
    my $status;
    my $file_name;

    $last = "NA";
    $status = "NA";
    $file_name = shift @_;
    open SRC_FILE, '<', $file_name or die "Failed to open file $file_name, $!";

    while (<SRC_FILE>) {
        chomp $_;
        if (/(^|\s+)typedef/ and /;$/) {
            if ($last ne "NA") {
                $status = "FIX";
                push @result, "\n$last\n";
                $last = "NA";
            }
            push @result, "$_\n" if /;$/;
        }

        $last = $_ if /#if\b/ or /#else/ or /#elif/;

        if (/#endif/ and $status eq "FIX") {
            $status = "NA";
            push @result, "$_\n";
        }
    }
    
    close SRC_FILE;
    @result;
};

sub scan_header_file_structure {
    my @result;
    my $file_name;
    my $status;

    $status = 0;
    $file_name = shift @_;
    open SRC_FILE, '<', $file_name or die "Failed to open file $file_name, $!";

    while (<SRC_FILE>) {
        chomp $_;
        if (/^\s*(struct|union|enum).* {/) {
            push @result, "$_\n";
            $status += 1;
        } elsif ("$status" ne "0") {
            push @result, "$_\n";
            $status -= 1 if /};/;
            push @result, "\n" if "$status" eq "0";
        }
    }

    close SRC_FILE;
    @result;
};

sub scan_source_file_implement {
    my @result;
    my $file_name;
    my $status;
    my $tmp;

    $tmp = "";
    $status = "LEAVE";
    $file_name = shift @_;
    open SRC_FILE, '<', $file_name or die "Failed to open file $file_name, $!";

    while (<SRC_FILE>) {
        chomp $_;
        if (/^(static|void|struct|bool)/ or /^[us]int(8|16|32|64)/) {
            $tmp = $_;
            $status = "ENTER";
        } elsif ($status eq "ENTER") {
            if (/^{/) {
                $status = "LEAVE";
                $tmp = $tmp . ";";
                push @result, "$tmp\n";
            } else {
                s/^\s+//;
                $tmp = "$tmp $_";
            }
        }
    }

    close SRC_FILE;
    @result = sort @result;
}

sub scan_header_file_definition {
    my @result;
    my $file_name;
    my $status;

    $status = "END";
    $file_name = shift @_;
    open SRC_FILE, '<', $file_name or die "Failed to open file $file_name, $!";

    while (<SRC_FILE>) {
        chomp;
        if (/^#define \w+(\(.*\))? /) {
            push @result, "$_\n";
            $status = "CONTINUE" if /\$/;
        } elsif ($status eq "CONTINUE") {
            push @result, "$_\n";
            $status = "END" unless /\$/;
        }
    }

    close SRC_FILE;
    @result;
};

1;

