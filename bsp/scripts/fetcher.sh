#!/bin/bash
#
# fetcher.sh copyright RidgeRun 2010
#
# 

DEBUG=""

while [ -n "$1" ] ; do
    case "$1" in

    --debug )
        shift
        set -x
        DEBUG="--debug"
        ;;

    *)
        echo "Warning: skipping unknown option: $1"
        shift
        ;;
    esac
done

DOWNLOADPATH=null

if [ "$VERBOSE" = "1" ] ; then\
    case $PKG_TARBALL in
        default )
            VERBOSE_ARGS="-v";
            ;;
    esac
else
    case $PKG_TARBALL in
        *.zip )
            VERBOSE_ARGS="-q";
            ;;
    esac
fi

#This function defines the package type based on its url 
#if it has not been defined before.
function  define_pkg_type {
    # If PKG_TYPE isn't defined, we guess it
    if [ -z "$PKG_TYPE" ] ; then
        if [[ $PKG_URL =~ "http://" ]] ; then
            PKG_TYPE=http
        elif [[ $PKG_URL =~ "https://" ]] ; then
             PKG_TYPE=https
        elif [[ $PKG_URL =~ "ftp://" ]] ; then
             PKG_TYPE=ftp
        elif [[ $PKG_URL =~ "git://" ]] ; then
             PKG_TYPE=git
        elif [[ $PKG_URL =~ "svn://" ]] ; then
             PKG_TYPE=svn
        else
             echo "    Error: can't infer package type from the PKG_URL. Aborting"
             exit 255
        fi
    fi

    # Sanity checks
    if [ $PKG_TYPE == "git" -o $PKG_TYPE == "svn" ] ; then
        if [[ ! $PKG_TARBALL =~ ".tar.bz2" ]] ; then
             echo "    Error: the PKG_TARBALL should have a tar.bz2 prefix if the package type is $PKG_TYPE. Aborting"
             exit 255
        fi
    fi
}

#This function handles any curl error due to some problem when
#trying to fetch the package using curl.
function handle_curl_error {
    ERR=$1
    PKG_NAME=$2
    WHAT=$3
    PKG_FILE=$4
    PKG_URL=$5

    rm -f $PKG_FILE

    #if the error was #22
    if [ $ERR -eq 22 ] ; then
	echo
	echo ERROR: Source package can not be found at $PKG_URL
	echo 
	return $ERR
    fi

    #on any other error code
    echo "Failure downloading $WHAT $PKG (curl error: $ERR) from $PKG_URL"
    return
}

#This function downloads the sha1sum file.
function process_sha1 {
    DIR=$1
    PKG=$2

    # If the PKG_TYPE is git or svn, we don't process sha1
    # Since by having the tarball it means we downloaded the code correctly
    if [ $PKG_TYPE == "git" -o $PKG_TYPE == "svn" ] ; then
        return;
    fi

    # Download sha1 if we don't have it
    if [ ! -f $DIR/$PKG.sha1 ] ; then
        # Make sure we can write the sha1 otherwise skip it
        if [ -d $DIR ] && [ -w $DIR ] ; then
            if [ -n "$PKG_SHA1SUM" ] ; then
                echo "$PKG_SHA1SUM  $PKG" > $DIR/$PKG.sha1
            else
                echo "  Downloading sha1sum file for $PKG from $url..."
                curl -f -L $url/$PKG.sha1 > $DIR/$PKG.sha1 || handle_curl_error $? $PKG sha1sum $DIR/$PKG.sha1  $url/$PKG.sha1
            fi
        fi
    fi
}

#This function verifies the sha1sum in order to check the 
#package's integrity.
function verify_pkg {
    DIR=$1
    PKG=$2

    # If the PKG_TYPE is git or svn, we don't process sha1
    # Since by having the tarball it means we downloaded the code correctly
    if [ $PKG_TYPE == "git" -o $PKG_TYPE == "svn" ] &&
        [ -f $path/$PKG_TARBALL ] ; then
        echo "    Download completed."
        touch $path/$PKG_TARBALL.verified
        DOWNLOADPATH=$path
        return 0;
    fi

    # If we already have the right tarball and the checksum
    # and create the verified file without having to re-download
    if [ -f $path/$PKG_TARBALL ] &&
        [ -f $path/$PKG_TARBALL.sha1 ] ; then
        pushd . >/dev/null
        cd $path
        if sha1sum -c $PKG_TARBALL.sha1 1>/dev/null 2>&1 ; then
            popd >/dev/null
            echo "    Download completed."
            touch $path/$PKG_TARBALL.verified
            DOWNLOADPATH=$path
            return 0;
        else
            popd >/dev/null
            echo ""
            echo "   Failure verifying sha1sum of existing file $path/$PKG_TARBALL"
            echo "   Manually remove invalid package using the following command:"
            echo "      rm -f $path/$PKG_TARBALL $path/$PKG_TARBALL.sha1"
            echo ""

            exit 255
        fi
    fi

    return 255
}

#This function downloads the package's tarball.
function get_tarball {
    DIR=$1
    PKG=$2
    URL=$3

    # Create tarball if we don't have it, that is download it from the url depending on the package type.
    if [ ! -f $DIR/$PKG ] ; then
        case $PKG_TYPE in
            http|ftp|https )
                echo "  Trying to download from ${url}/$PKG_TARBALL to $DIR..."
                # Download the package
                #-L : Follows all redirections until the final destination page is found.
                #     This switch is almost always required as curl won’t follow redirects by default
                curl -f -L --limit-rate $FETCHER_MAX_DOWNLOAD_RATE  $URL/$PKG > $DIR/$PKG || { handle_curl_error $? $PKG package $DIR/$PKG $URL/$PKG ; rm -rf $DIR/$PKG ; return 255; };
                ;;
            git )
                echo "    Trying to clone $PKG_URL..."
                #Create a temporal directory where we will download the package
                rm -Rf /tmp/rrsdk_$$/$PKG_NAME
                mkdir -p /tmp/rrsdk_$$/
                #Remember the current directory
                pushd . >/dev/null
                #Got to the temporal and clone the app
                cd /tmp/rrsdk_$$/
                git clone $URL $PKG_NAME || { echo "Failed cloning git repository $PKG_URL." ; return 255; }
                cd $PKG_NAME
                #If a specific revision was set, branch the package to it.
                if [ -n $PKG_REVISION ] ; then
                    git checkout -b stable $PKG_REVISION || { echo "Failed to branch to the specified package revision: $PKG_REVISION" ; exit 255; }
                fi
                #Create the package tarball
                tar $VERBOSE_ARGS -cjf $DIR/$PKG .
                #Jump to previous directory
                popd >/dev/null
                #Remove temporal directory
                rm -Rf /tmp/rrsdk_$$/$PKG_NAME
                ;;
            svn )
                echo "    Trying to checkout $PKG_URL..."
                #Create a temporal directory where we will download the package
                rm -Rf /tmp/rrsdk_$$/$PKG_NAME
                mkdir -p /tmp/rrsdk_$$/
                #Remember the current directory
                pushd . >/dev/null
                #Go to the temporal and checkout the package
                cd /tmp/rrsdk_$$/
                svn co $SVN_AUTH_ARGUMENTS $URL $PKG_NAME || { echo "Failed checking out repository $PKG_URL." ; return 255; }
                cd $PKG_NAME
                #If a specific revision was set, branch the package to it.
                if [ -n $PKG_REVISION ] ; then
                    svn up $SVN_AUTH_ARGUMENTS  -r $PKG_REVISION || { echo "Failed to update to the specified package revision: $PKG_REVISION" ; exit 255; }
                fi
                #Create the package tarball
                tar $VERBOSE_ARGS -cjf $DIR/$PKG .
                #Jump to previous directory
                popd >/dev/null
                #Remove temporal directory
                rm -Rf /tmp/rrsdk_$$/$PKG_NAME
                ;;
            * )
                #The package type specified is not valid
                echo "    Unknown kind of PKG_TYPE: $PKG_TYPE. Aborting"
                exit 255;
        esac
    fi
}

#This function handles the download process: fetch the package, download the
#sha1sum and verify the package.
function download {
    url="$1"

    # Find if we already have the file
    for path in $DOWNLOADS ; do
        if [ -f $path/$PKG_TARBALL ] ; then
            if [ -f $path/$PKG_TARBALL.verified ] ; then
                DOWNLOADPATH=$path
                echo "    Found $PKG_TARBALL on $path (verified)"
                return 0
            fi

            result=eval process_sha1 "$path" "$PKG_TARBALL"
            if ! $result ; then 
                return $result
            fi

            if verify_pkg "$path" "$PKG_TARBALL" ; then
                DOWNLOADPATH=$path
                return 0;
            fi
            return 255
        fi
    done

    # Didn't find the package, download to the first directory which we can write to
    for path in $DOWNLOADS ; do
       DOWNLOAD_RETRY=0
       if [ -d $path ] && [ -w $path ] ; then

           while [ "$DOWNLOAD_RETRY" -lt "$FETCHER_MAX_DOWNLOAD_RETRIES" ] ; do
               # Try to get the tarball
               get_tarball  "$path" "$PKG_TARBALL" "$url"
               # If the tarball was downloaded without errors
               if [ 0 == $? ]; then
                   #Download sha1sum file
                   process_sha1 "$path" "$PKG_TARBALL"
                   #Verify the package integrity
                   if verify_pkg "$path" "$PKG_TARBALL" ; then
                       #If everything is correct, then set the path where we download the package.
                       DOWNLOADPATH=$path
                       return 0
                   fi
               else
                   if [ "$FETCHER_DOWNLOAD_RETRY" == yes ] ; then
                       DOWNLOAD_RETRY="$(( $DOWNLOAD_RETRY + 1 ))"
                   else
                       DOWNLOAD_RETRY=$FETCHER_MAX_DOWNLOAD_RETRIES
                   fi

                   if [ "$DOWNLOAD_RETRY" == "$FETCHER_MAX_DOWNLOAD_RETRIES" ] ; then
                       #If there was an error, return to the previous directory (if it is necessary) 
                       #and return with error.
                       popd &> /dev/null
                       return 255
                   else
                       echo "Unable to reach package, trying again in $FETCHER_DOWNLOAD_RETRY_DELAY seconds"
                       sleep $FETCHER_DOWNLOAD_RETRY_DELAY
                   fi
               fi
           done
        fi
    done

    if [ "$DOWNLOADPATH" == "null" ] ; then
        echo -e "    Aborting. No write permission for any download folder.\nPaths are: $DOWNLOADS";
        return 255;
    fi
}

#This function unpacks the package to the app's directory.
function unpack {

    if [ ! -z "$FETCHER_EXTRACT_DIRECTORY_NAME" ] ; then
        DIRNAME=$FETCHER_EXTRACT_DIRECTORY_NAME
        TAR_ARGS="$TAR_ARGS --strip 1"
    else
        DIRNAME=$PKG_NAME
    fi
    mkdir -p $DIRNAME

    if [ -f rrfetched ] ; then
        return 0
    fi

    pushd . >/dev/null
    echo "    Unpacking $PKG_TARBALL... "
    cd $DIRNAME
    case $PKG_TARBALL in
        *.tar.gz | *.tgz)
            tar $VERBOSE_ARGS $TAR_ARGS -xzf $DOWNLOADPATH/$PKG_TARBALL
            ;;
        *.tar.bz2 )
            tar $VERBOSE_ARGS $TAR_ARGS -xjf $DOWNLOADPATH/$PKG_TARBALL
            ;;
        *.tar.xz )
            # On recent distros tar supports xz natively, but we need backwards comaptibility
            unxz -c $DOWNLOADPATH/$PKG_TARBALL | tar $VERBOSE_ARGS $TAR_ARGS -x 
            ;;
        *.gz )
            gunzip $VERBOSE_ARGS $DOWNLOADPATH/$PKG_TARBALL 
            ;;
        *.zip )
            unzip $VERBOSE_ARGS $DOWNLOADPATH/$PKG_TARBALL
            mv $PKG_ZIP_STRIP_DIR/* . >/dev/null
            rm -Rf $PKG_ZIP_STRIP_DIR
            ;;
        *.tar )
            tar $VERBOSE_ARGS $TAR_ARGS -xf $DOWNLOADPATH/$PKG_TARBALL
            ;;
        *.bin )
            chmod +x $DOWNLOADPATH/$PKG_TARBALL
            if [ ! -z "$BIN_ANSWERS" ] ; then 
                echo -e "$BIN_ANSWERS" | $DOWNLOADPATH/$PKG_TARBALL $BIN_ARGUMENTS
            else
                $DOWNLOADPATH/$PKG_TARBALL $BIN_ARGUMENTS
            fi
            ;;
        default )
            echo "Unknown package type, can't handle it"
            return 255
            ;;
    esac
    popd > /dev/null

    touch rrfetched || { echo "Can't create file rrfetched" ; return 255 ; }

    return 0
}

#First try the internal download server, second the package's url,
#then RR's server 
URLS=($PKG_INTERNAL_URL $PKG_URL $DOWNLOAD_SERVER);

ORIG_PKG_URL=$PKG_URL
ORIG_PKG_TYPE=$PKG_TYPE

#For each URL in our list
for url in "${URLS[@]}" ; do
    #Set current url to the PKG_URL variable
    PKG_URL=$url

    # We only respect the PKG_TYPE value for the original URL, for the fallback
    # links it could have other types, so we fallback to autodetection
    if [ "$PKG_URL" == "$ORIG_PKG_URL" ] ; then
        PKG_TYPE=$ORIG_PKG_TYPE
    else
        PKG_TYPE=""
    fi

    #Define the package type if it was not specified before on Makefile.
    define_pkg_type
    #Try to download the package.
    if download $url ; then
        #If the package was succesfully downloaded we unpack it.
        result=eval unpack;
        exit $result;
    fi;
done

#If we were not able to download the package exit with error.
echo
echo "Unable to download package $PKG_TARBALL."
echo "Please contact RidgeRun for support."
echo
exit 255;
