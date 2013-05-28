#!/usr/bin/perl

use warnings;
use Getopt::Long;
use Term::ReadKey;

#General-purpose string trimming subroutine (removes leading and trailing blanks).
sub trim{
    my $string = shift;
    $string =~ s/^\s+|\s+$//g;
    return $string;
}

#Stores the current release version.
my $current_upd;
#Stores the release version to which the script is presently trying to upgrade.
my $target_upd = "";
#Stores the location for the .release file containing information on current and available versions.
my $release_file = "../.updates";

#Obtains the intended target update if the update optional parameter is used.
GetOptions("update=s" => \$target_upd);

open (REL_FILE, $release_file) || die "Couldn't find release information file!\n";

#Obtains release name and current release version from the info. file.
my $release_name = <REL_FILE>;
$release_name = trim($release_name);
$current_upd = <REL_FILE>;
$current_upd = trim($current_upd);

#Obtains the latest available update and forms a list of all available updates.
my $last_upd;

my $available_updates = "";

while(my $update = <REL_FILE>){
    $available_updates .= $update;
    $last_upd = $update;
}

#Shows error if there're no updates available for this release.
if(!defined($last_upd)){
    print "\n  No available updates detected; either there are no updates available for this SDK release at the moment or the local update list is outdated.\n";
    print "  Run the \"show_updates\" command if you suspect the later might be the case to check for available updates.\n\n";
    
    exit(0);
}

#Trims value for latest available release (may have leading/trailing spaces).
$last_upd = trim($last_upd);

#Obtains array and count of available updates (not counting the one it's currently targeting).
my @updates = split('\n', $available_updates);
pop(@updates);
my $updates = @updates;
$updates--;

#Trims value for latest available release (may have leading/trailing spaces).
$last_upd = trim($last_upd);

#If the update option wasn't used, ask if it should default to the latest available update.
if($target_upd eq ""){
    print "\n  No update specified through --update flag.\n  Update to latest version available: $release_name\.$last_upd? ";
    print "(y/n)";
    my $ans = trim(ReadLine(0));
    if($ans eq "y" || $ans eq "Y"){
		#Set target update as the latest available update detected.
		$target_upd = $last_upd;
    }
    else{
		print "\n";
		exit(0);
    }
}

#If the update to which the upgrade is required is specified but is invalid, complain.
elsif(int($target_upd) <= int($current_upd)){
	print "\n  Invalid update number specified (Current SDK version: $current_upd).\n\n";
	exit(0);
}

print "\n  Testing updates $release_name.$current_upd through $release_name.$target_upd...\n\n";

#Ask for user credentials.
print "  Username: ";
my $username = trim(ReadLine(0));
print "  Password: ";
ReadMode('noecho');
my $password = trim(ReadLine(0));
ReadMode('normal');

#Test for conflicts.
my $added = 0;
my $moved = 0;
my $deleted = 0;
my $updated = 0;
my $merged = 0;
#Default conflicts = 1 so it enters the testing loop.
my $conflicts = 1;
my $run = 0;

#default values for binary search logic.
my $high = $updates;
my $middle = $updates;
my $low = 0;

while ($conflicts != 0){

#Clear counts.
$added = 0;
$moved = 0;
$deleted = 0;
$updated = 0;
$merged = 0;
$conflicts = 0;
    
	#Obtain preview of results through the --dry-run flag.
	
    my $test_result = `svn merge --dry-run -r $current_upd:$target_upd . --username $username --password $password`;
    print $test_result;
    my @lines = split /\n/, $test_result;

    foreach my $line (@lines) {
	if($line =~ /^A/) { $added++; }
        if($line =~ /^U/) { $updated++; }
        if($line =~ /^D/) { $deleted++; }
        if($line =~ /^G/) { $merged++; }
        if($line =~ /^C/) { $conflicts++; }
    }

	#Binary search logic triggers in case there's a conflict during upgrade attempt:
    if($conflicts>0){

		#If there's no available conflict-free update:
		if($high == $low){
			print "All available updates compromise SDK integrity. Please contact RidgeRun support to manually apply the update.\n\n";
			exit(0);
		}        
		
		#If it's the first iteration of the binary search, ask if it should look for intermediate updates.
		if($run == 0){
			print "\n\n  The update can't be performed due to existing conflicts in the current version and the requested update. Look for intermediate updates?";
			print " (y/n)";
			my $ans = trim(ReadLine(0));
			
			if($ans eq "y" || $ans eq "Y"){
				#Start binary search logic.
				print "\n  Looking for latest non-conflicting update available, please wait.\n\n";
				#Calculate middle update to start checking for intermediate updates.
				$middle = $low + (($high-$low)/2);
				$target_upd = $updates[$middle];
			}
			
			else{
				print "\n";
				exit(0);
			}
			
			$run ++;
		}
		#If it's not the first iteration, continue with the binary search "to the left".
		else{
			#Dispose of target updates starting from the previous target. 
			$high = $middle-1;
			#Calculate middle update of whatever updates are left. 
			$middle = $low + (($high-$low)/2);
			$target_upd = $updates[$middle];
		}
		
    }	
    elsif($run > 0){
		#Found an available update but it might not be the latest available. Keep searching "to the right"
		#(unless this *is* the latest one available = middle equals high).
		if($middle != $high){
			$low = $middle;
			$middle = $low + (($high-$low)/2);
		}
		
		#Found a valid update. Get out of the loop and report.
		else{
			print "  Update $release_name.$target_upd is available without existing conflicts:"
		}
    }
}

print "\n\n";

#Show update preview
if($added > 0){ print "  $added file(s) to be added.\n" }
if($updated > 0){ print "  $updated file(s) to be updated.\n" }
if($moved > 0){ print "  $moved file(s) to be moved.\n" }
if($deleted > 0){ print "  $deleted file(s) to be deleted.\n" }
if($merged > 0){ print "  $merged file(s) to be merged.\n" }

#Ask to apply changes
print "\n  Apply changes? (y/n)";

my $ans = trim(ReadLine(0));

#Perform upgrade
if($ans eq "y" || $ans eq "Y"){
    print "\n  Performing updates, please wait and refrain from interrupting this operation...";

    my $results = `svn merge -r $current_upd:$target_upd . --username $username --password $password`;
    print $results;
    
    #edit release information file to reflect the performed results.
    open (REL_FILE, ">$release_file") || die "Couldn't load release file for writing";
    print REL_FILE "$release_name\n";
    print REL_FILE "$target_upd\n";
	
    #Print available updates in case this was a partial upgrade
	$middle++;
    for(;$middle < $updates;$middle++){
		print REL_FILE "$updates[$middle]\n";
    }
    
    print "\n  Changes applied. Current SDK version: $release_name.$target_upd. \n\n";
}

else { print "\n"; }
