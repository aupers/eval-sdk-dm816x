#!/bin/sh
autoreconf -fi || {
 echo 'autogen.sh failed';
 exit 1;
}
