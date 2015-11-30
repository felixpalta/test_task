# test_task

# Requirements
- C++11 support
- POSIX environment

# Description
Server and client for LED control.
LED operation is emulated by printing LED state changes to stdout.

# Build instructions

    cd test_task/server
    ./build.sh output_dir

# Start server
    cd output_dir
    chmod +x server
    ./server pipe_to_server pipe_from_server
    
The server logs internal errors to stderr.

     ./server /tmp/toserver /tmp/fromserver 1> led.log 2> server.log # server will create the fifo pipes

To see help run `server` without parameters.


# Use client
    ./client.sh pipe_to_server pipe_from_server [REQUEST] [PARAM] [NEW_VALUE(only for --set)]
    
e.g. 

     ./client.sh /tmp/fromserver /tmp/toserver --set color RED

    REQUESTs:
      --get
      --set
  
    PARAMs and NEW_VALUEs:
        color [RED|GREEN|BLUE]
        state [ON|OFF]
        rate [0..5]

To see help run `client.sh` without parameters.

Client returns 0 if transaction succeeded and server returned OK, otherwise returns 1.
In case of successful --get request the client prints value returned from server to stdout.
