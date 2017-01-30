#!/bin/sh
# Simple slapper to test connections to fcgiwrapper.sock
# Change the below variable to your actual socket path
SOCK_PATH=/var/tmp/fcgiwrap.sock

if [[ -e $SOCK_PATH ]];
then
    /root/bin/test_fcgi
    if [[ $? != 0 ]];
    then
        rm $SOCK_PATH
        /usr/local/etc/rc.d/fcgiwrap restart
    fi;
fi;
