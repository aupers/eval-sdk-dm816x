#!/usr/bin/perl

my $replacement;
{
    local $/;
    my $file = shift;
    open my $fh, "<$file";
    $replacement=<$fh>;
}

while (<>)
{
    if (!/\$L\$/)
    {
        print;
    }
    else
    {
        last;
    }
}

print $replacement;

while (<>)
{
    last if /\$L\$/;
}

while (<>)
{
    print;
}
