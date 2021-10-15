## Code

Each of the folders client_* and server_* must compile into 4 distinct exectutables:
`chatserver_tcp, chatclient_tcp, chatserver_udp, chatclient_udp`

You are welcome to use any other file structure and modify the makefile, but we are not responsible if the
comilation doesn't work on the autograder. You are welcome to add any libraries in the compiler (We automatically include the pthreads library), as long as they are part of the standard c++ libraries.

## Compilation

Simply run `make build-[server|client]_[tcp|udp]` to compile a specific program, or `make` to compile everything

## Submission

To submit with the standard file stucture, simply run `make submit` to generate a zip file with the cpp files. otherwise
make sure the four executables are correctly generated.