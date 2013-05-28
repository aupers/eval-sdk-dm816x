#!/usr/bin/perl

use strict;
use warnings;

use YAML;
use Data::Dumper;

my $testcase = YAML::LoadFile("$ARGV[0]") || die "Failed to load yaml file. Aborting";

#print "Testcase name is: '$testcase->{\"Name\"}'\n";
print Dumper($testcase), "\n";

