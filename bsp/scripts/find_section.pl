#!/usr/bin/perl

my $start = shift;
my $end = shift;

while (<>)
{
    last if /$start/;
}

while (<>)
{
    if (/$end/)
    {
        last;
    } else {
        print;
    }
}
# Just in case we don't have a line change
if (eof && 
    !($_ =~ /$start/) && 
    !($_ =~ /$end/)
    ) {
    print;
}