#!/bin/bash

if [ $# -lt 1 ] 
then echo "Usage: $0 server_pipe"; exit 1; 
fi

PIPE=$1

function test_state {
    ./client.sh "$PIPE" --set state "$1" || echo "error on set" && result=`./client.sh "$PIPE" --get state` || echo "error on get"

    if [[ !"$result" == "$1" ]];
    then
    echo "unexpected result: ""$result"; exit 1;
    fi
}

test_state "ON"
test_state "OFF"
