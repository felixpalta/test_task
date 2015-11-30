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
    ./server server_pipe
    
The server logs internal errors to stderr.

     ./server /tmp/server_pipe 1> led.log 2> server.log # server will create fifo if it does not exist yet

To see help run `server` without parameters.


# Use client
     ./client.sh server_pipe [REQUEST] [PARAM] [NEW_VALUE(only for --set)]
    
e.g. 

     ./client.sh /tmp/server_pipe --set color RED

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

# How it all works

Server constantly listens to `server pipe`.
Each new client generates a unique ID and a unique pipe, i.e. `client pipe ID`.
The client sends its client pipe name to server thorugh `server pipe`.
After that client writes a request to the `client pipe` and waits for the server to read it.
When server receives a `client pipe ID` it creates a new task and adds it to the task queue.
In each task, the `client pipe` is opened and a request is read from it. The request is then processed and a reply is written
back to the same `client pipe`.
When client has successfully finished writing request to `client pipe` it knows that the server has consumed it, so 
at this point client can open the `client pipe` for reading on order to receive the reply.

The client script processes its parameters (user-client portocol) on order to produce valid request according to the client-server protocol,
then parses the server reply in order to return it according to user-client protocol.
