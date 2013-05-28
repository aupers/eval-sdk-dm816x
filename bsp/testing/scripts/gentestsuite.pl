#!/usr/bin/perl

# Copyright 2011, RidgeRun

use strict;
use warnings;
use File::Find;
use Term::ANSIColor qw(:constants);
use YAML;
use Data::Dumper;
use XML::Writer;

$Term::ANSIColor::AUTORESET = 1;

my $DEVDIR=$ENV{'DEVDIR'};

if ($DEVDIR eq "") {
    fatal_error("Your DEVDIR variable isn't set, unable to build the testsuite.");
}


# ==============================================================================
# Global Structures
# ==============================================================================

# This is the tree that will contain the parsed content and then be 
# parsed to create the resulting xml file

my %test_tree;

# This is a temporal array that holds all testcases for two reasons:

# > So that the file structure doesn't have to be parsed twice
#   (once for suites and another for cases)
# > So that test cases are added to the tree only after categories have 
#   been parsed.

my @test_cases;

# ==============================================================================
# Init. Instructions
# ==============================================================================

# Find files
find(\&testcase_filter, "$DEVDIR/bsp" );

#print Dumper(@test_cases), "\n";

# Add all test cases to the tree
testcase_handle();

# Dump the XML
dump_xml();

# ==============================================================================
# Functions
# ==============================================================================

sub fatal_error{
    print RED "\nError: ";
    print "@_\n\n";
    exit 255;
}

# Depth first search for heriarchical categorization of tests and test sub-categories.

sub find_parent{
    my $hash = $_[0];
    my $current_key = $_[1];
    my $search_key = $_[2];

    # print "\n CurrentKey: $current_key \n hash: $hash \n search: $search_key\n\n";

    my $new_hash = \%{$hash->{$current_key}};

    if(! defined $new_hash->{"TestCase"}){

	if($current_key eq $search_key){
	    # print "found!\n";
	    # print Dumper(%{$hash->{$current_key}});
	    return $new_hash;
	}
    
	else{
	if(keys %{$new_hash}){
	
	    # Recursive magic
	    foreach my $slkey (keys %{$new_hash}){
	
		    #Recursion. Don't look at it directly or eye damage may occur.
		    my $result = find_parent($new_hash, $slkey, $search_key);
		    if($result){
			return $result;
		        last;
			}
	    }
	}
	}
    }
}

# Function that handles testcases found.

sub testcase_handle{

    foreach my $testcase (@test_cases){

    #print "Testcase Name: '$testcase->{\"TestCase\"}' \n";
    # Gotta each case's parent suite:

    my $test_tree = \%test_tree;
    foreach my $key (keys %test_tree){
	my $hash = find_parent($test_tree, $key, $testcase->{"TestSuiteCat"});
        if($hash){
		$hash->{$testcase->{"TestCase"}} = $testcase;
		last;
	}
    }
    }
    #print "Testcase name: '$testcase->{\"TestCase\"}'\n";
    #print Dumper($testcase), "\n";
}


# Function that handles testsuites found.

sub testsuite_handle{

    my $testsuite = $_[0];

    #print "Testsuite Name: '$testsuite->{\"TestSuite\"}' \n";

    if(defined $testsuite->{"TestSuiteCat"}) {

	# Gotta find the parent suite:
	
	my $test_tree = \%test_tree;
	foreach my $key (keys %test_tree){
	    my $hash = find_parent($test_tree, $key, $testsuite->{"TestSuiteCat"});
	    if($hash){
		$hash->{$testsuite->{"TestSuite"}} = {};  #"Hello" => $testsuite->{Summary}};
		last;
	    }
	}
    }

    # Belongs to no category.

    else {
	$test_tree{$testsuite->{"TestSuite"}} = {};
    }

}

# YAML File finder

sub testcase_filter {

    # Behold, human, regular expressions.

    if ($File::Find::name =~ m/.*\/rrtest\/.*\.yaml$/ &&
        !($File::Find::name =~ m/bsp\/testing\/examples\// )) {

	# Load found file to $found variable

	my $found = YAML::LoadFile($File::Find::name) || die "Failed to load YAML file
. Aborting.";

	# Decides whether file contains a testcase or a testsuite description
	# and calls the appropriate handler:

        if ( defined $found->{"TestCase"} ) {
    	    push(@test_cases, $found);
        }

        elsif ( defined $found->{"TestSuite"} ) {
    	    testsuite_handle($found);
        }
    }
}

# Auxiliary recursive subroutine for the dump_xml sub.

sub dump_xml_recursive {

    my $root = shift;
    my $tree = shift;
    my $writer = shift;

    #Case: Testcase

    my $new_root = \%{$root->{$tree}};

    if(defined $new_root->{"TestCase"}){
	$writer->startTag('testcase', 'name', $tree);
	$writer->startTag( 'details' );
	$writer->cdata( '' );
	$writer->endTag();
	
	#summary
	
	$writer->startTag( 'summary' );
	$writer->cdata( $new_root->{"Summary"} );
	$writer->endTag();	
	
	#steps
	
	$writer->startTag( 'steps' );
	$writer->startTag( 'step' );
	
	    # Step number. This is wired since we don't really like
	    # TestLink's "one result per step" approach, and instead 
	    # describe all steps and results on the same "step".
	
	    $writer->startTag( 'step_number' );
	    $writer->cdata( "1" );
	    $writer->endTag();
	
	    #Steps go here
	
	    $writer->startTag( 'actions' );
	    $writer->cdata( $new_root->{"Steps"} );
	    $writer->endTag();
	
	    #Expected results go here
	
	    $writer->startTag( 'expectedresults' );
	    $writer->cdata( $new_root->{"ExpectedResults"} );
	    $writer->endTag();
	
	    # This "Execution Type" variable stands for either manual or
	    # automatic. Maybe eventually this will stop being a wired value.
	
	    $writer->startTag( 'execution_type' );
	    $writer->cdata( $new_root->{"1"} );
	    $writer->endTag();
	
	
	$writer->endTag();
	$writer->endTag();
	
	#expectedresults
	
	#$writer->startTag( 'expectedresults' );
	#$writer->cdata( $new_root->{"ExpectedResults"} );
	#$writer->endTag();

	$writer->endTag();
    }

    # Case: TestSuite, gotta use the recursion wand again.

    else{
	
	$writer->startTag('testsuite', 'name', $tree);
	$writer->startTag( 'details' );
	$writer->cdata( '' );
	$writer->endTag();

	if(keys %{$root->{$tree}}){

	foreach my $key (keys %{$root->{$tree}}){
	
	    #Recursion. Don't look at it directly or eye damage may occur.
	    dump_xml_recursive($new_root, $key, $writer);
	
	    }
        }

	$writer->endTag();
    }
}

# Dumps the parsed content into a XML file.

sub dump_xml {

    # Creates output file

    my $output;
    open($output, '>', 'output.xml') || die "Unable to create output file!";
    my $xml_writer = new XML::Writer( OUTPUT => $output);

    # Creates header and root tag

    $xml_writer->xmlDecl( 'UTF-8' );
    $xml_writer->startTag( 'testsuite', 'name', 'RidgeRun SDK Testing' );
    $xml_writer->startTag( 'details' );
    $xml_writer->cdata( '' );
    $xml_writer->endTag();

    # Traverses tree and dumps info to the XML file

    my $test_tree = \%test_tree;

    foreach my $key (keys %test_tree){
	dump_xml_recursive($test_tree, $key, $xml_writer);
    }

    # Closes header tags and document.

    $xml_writer->endTag();
    $xml_writer->end();
}