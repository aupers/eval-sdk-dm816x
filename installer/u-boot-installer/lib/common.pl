# ==============================================================================
# dbg
# ==============================================================================
sub dbg
{
    if ($ENABLE_DEBUG > 0) {
        print @_;
    }
}
# ==============================================================================
# vdbg
# ==============================================================================
sub vdbg
{
    if ($ENABLE_DEBUG > 1) {
        print @_;
    }
}

sub cmd_echo {
    print "     $_[0]\n";
    system("$_[0] $_[1]") && ( do_cleanup() || die "Failed executing last command") ;
}

sub cmd_silent{
    if ($ENABLE_DEBUG > 0) {
	print "     $_[0]\n";
    }
    system("$_[0] $_[1]") && ( do_cleanup() || die "Failed executing last command") ;
}

sub fatal_error {
    print RED "\n  Error: ";
    print "$_[0]\n\n";
    exit -1;
}

sub mydie{
    do_cleanup();
    die $@;
}

sub do_cleanup(){
    if ($CONFIG_INSTALLER_MODE_ATTACHED_BOARD eq "y") {
        attached_cleanup();
    } elsif ($CONFIG_INSTALLER_MODE_SD_CARD eq "y") {
        sd_cleanup();
    } elsif ($CONFIG_INSTALLER_MODE_SD_CARD_INSTALLER eq "y") {
        attached_cleanup();
        sd_cleanup();
    } else {
        printf "\nCleanup not implemented for this installation mode...\n\n";
    }
}

sub check_device_is_not_mounted {
    $DEVICE = $_[0];

    if (! system ("grep -q $DEVICE /proc/mounts") ||
        ! system ("grep -q $DEVICE /proc/mdstat")){
        print RED "  WARNING!\n";
        print "  Your device $DEVICE seems to be either mounted, or belongs\n";
        print "  to a RAID array in your system\n";
        print "\n  Refusing to run the deploy over $DEVICE. Please check that this device is not mounted\n\n";
        exit -1;
    }
}

1;
