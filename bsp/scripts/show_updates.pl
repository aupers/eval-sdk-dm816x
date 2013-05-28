#!/usr/bin/perl

##
# show_updates.pl Copyright RidgeRun 2011
#
#

use warnings;
use LWP::UserAgent;
use HTTP::Request;
use HTTP::Request::Common;
use Term::ReadKey;
use Getopt::Long;

# set default value for option
my $revision = 0;
my $showdirs = 0;
my $getupdates = 0;

# get value of flags (if any)
GetOptions("revision=s" => \$revision,
	   "showdirs=s" => \$showdirs,
	   "getUpdates=s" => \$getupdates);

# A trim subroutine to ensure a pretty output in case the update comments decide
# to sneak in a couple of newlines into the output or something of the sort, as
# well as remove the trailing newline for the user and password input.

sub trim{
    my $string = shift;
    $string =~ s/^\s+|\s+$//g;
    return $string;
}

# Required files

my $dev_url = $ENV{'DEVDIR'};

my $update_file = $dev_url . "/bsp/.updinfo";
my $release_file = $dev_url . "/bsp/.release";
my $av_updates_file = $dev_url . "/bsp/.updates";

#Webservice URL

my $url = 'https://source.ridgerun.net/webservices/updates/';

#Reads and gathers information from the required files

open (UPD_FILE, $update_file) || die "Couldn't find update information file!";
open (REL_FILE, $release_file) || die "Couldn't find release information file. This is not a valid RidgeRun SDK release.";

#Obtains release version
my $release = <REL_FILE>;

#Obtains revision number
my $revision_num = <REL_FILE>;

#Obtains build directories
my $directories = "";

while(my $dir = <UPD_FILE>){
    $directories .= $dir;
}

print "  In order to establish contact with RidgeRun's servers and check if any updates are available for this SDK, specifiy your username and password as provided by RidgeRun support below for authentication.\n";
my $try = 3;

my $response;

while($try > 0){
    if($try < 3){print " Authentication failed. ", $try, " tries left.\n";}
    # Obtains user and password for authentication into the server:
    print "\n Username: ";
    my $user = trim(ReadLine(0));
    ReadMode('noecho');
    print " Password: ";
    my $password = trim(ReadLine(0));
    ReadMode('normal');

    print "\n\n [Contacting server...]\n\n";

    # Sends POST Request
    my $browser = LWP::UserAgent->new;

    # Adds required credentials
    $browser->credentials(
        'source.ridgerun.net:443',
        'RidgeRun Update Server',
         $user => $password
    );

    $response = $browser->post($url, [
        release => "$release",
        revision => "$revision_num",
        directories => "$directories",
        revision_opt => "$revision",
        show_dirs => "$showdirs",
        featureTest => "1"
    ]);

    if($response->is_success){$try = -5;}

    $try--;
}

if($response->is_success){
    my $updates = $response->content;

    my @updates_content = split(/UPD_LIST/, $updates);
    my $count = @updates_content;
    if($count > 0){

	print " Server response obtained. Updates shown below: \n\n";

	print " ==========================================\n";
	
	print $updates_content[0];

	print "\n ==========================================\n\nIf you want to upgrade to any of the available updates shown above, please contact RidgeRun support and request an upgrade operation.\n\n";
	
	
	if($getupdates == 1){
	    open (DEV_FILE, ">$av_updates_file") || die "Couldn't find update information file!";
	
	    print DEV_FILE $release;
	    print DEV_FILE "$revision_num\n";
	    print DEV_FILE $updates_content[1];
	}	
    }
    else{
	print " Server response obtained. There are no available updates for this SDK release at the moment. \n\n";
    }
}
else{
    print " Error getting $url: Either the username and password combination is incorrect or the server is not available.\n\n";
    print $response->content;
}
exit 0;