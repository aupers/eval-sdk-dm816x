#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

#! /bin/bash

# fail after something went wrong
set -e

# cmdline arguments
readonly OUTPUT="components.xml"

# create empty list of all txt files
TXTS=""

# add all txt files
TXTS="$TXTS copyrights-links"

# create the txt files, install them in $(FSROOT)/usr/share and check if the package license is online
for TXT in $TXTS
do
	xsltproc -o $TXT.txt  $TXT.xsl $OUTPUT
	for line in $(cat copyrights-links.txt) ;
                do                                                      
                        if ! wget -nv -q -O - $line > /dev/null;
                        then                                            
                                echo "$line seems to be offline";
                                exit 1;      
                        fi                                            
                done 
	rm $TXT.txt
done

exit 0
