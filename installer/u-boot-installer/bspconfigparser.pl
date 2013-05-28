#!/usr/bin/perl

open FH, "<", "$ARGV[0]" or die $!;

while (<FH>)
{
    if (($_ =~ /=/) && 
	($_ =~ /BTLR/ || $_ =~ /INSTALLER/ || $_ =~ /UBOOT/ || $_ =~ /FS_TARGET/ )) {
	my @VALUE = split(/=/,$_,2);
	chomp(@VALUE[1]);
	if (@VALUE[1] =~ /^\".*\"/) {
	    print "our \$@VALUE[0] = @VALUE[1];\n";
	} else {
	    print "our \$@VALUE[0] = \"@VALUE[1]\";\n";
	}
    }
}

# ==============================================================================
# Delete quotes
# First param: String with quotes
# ==============================================================================
sub delete_quotes() {
    my @ARRAY = split(/\"/,$_[0]);
    return @ARRAY[1];
}
