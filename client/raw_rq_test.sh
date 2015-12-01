#!/bin/bash

if [ $# -lt 2 ];
then
echo "Usage: $0 server_pipe \"request\""; exit 1
fi

SERVER_PIPE=$1
RQ=$2

CLIENT_PIPE="/tmp/raw_test_client"

if [ ! -p "$CLIENT_PIPE" ];
then mkfifo "$CLIENT_PIPE";
fi

echo "$CLIENT_PIPE" > "$SERVER_PIPE" &&
  echo "$RQ" > "$CLIENT_PIPE" &&
    cat "$CLIENT_PIPE"; 

rm -f "$CLIENT_PIPE"
