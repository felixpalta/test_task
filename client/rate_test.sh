#!/bin/bash

if [ $# -lt 1 ] 
then echo "Usage: $0 server_pipe"; exit 1; 
fi

PIPE=$1

function test_rate {
    ./client.sh "$PIPE" --set rate "$1" || echo "error on set" && result=`./client.sh "$PIPE" --get rate` || echo "error on get"

    if [[ !"$result" == "$1" ]];
    then
    echo "unexpected result: ""$result"; exit 1;
    fi
}

test_rate 0
test_rate 1
test_rate 2
test_rate 3
test_rate 4
test_rate 5

