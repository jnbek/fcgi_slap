#!/bin/sh
# Simple slapper to test connections to fcgiwrapper.sock
# Change the below variable to your actual socket path
# and path/filename for your slapper program

SOCK_PATH=/var/tmp/fcgiwrap.sock
SOCK_SLAPPER=/root/bin/test_fcgi

if [[ -e $SOCK_PATH ]];
then
    $SOCK_SLAPPER
    if [[ $? != 0 ]];
    then
        rm $SOCK_PATH
        /usr/local/etc/rc.d/fcgiwrap restart
    fi;
fi;
