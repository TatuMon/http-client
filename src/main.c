#include "conn.h"
#include "sys/socket.h"
#include "utils.h"
#include "netinet/in.h"
#include "stdio.h"
#include "unistd.h"
#include "getopt.h"

/**
 * Parse the command's arguments, storing the values in the appropiate pointers.
 * */
void parseCmdArgs(
    int argc,
    char** argv,
    const char* port,
    const char* body
) {
    struct option options[] = {
        { "port", required_argument, 0, 'p' },
        { "body", optional_argument, 0, 'b' },
    };
    const char* optstring = "p:b:";
}

int main(int argc, char** argv) {
    const char* port;
    const char* body;

    if (argc < 2) {
        exit_err("Must provide target address");
    }
    const char* targetAddress = argv[1];




    FileDesc client_socket = establishConnection(targetAddress, port);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    getsockname(client_socket, (struct sockaddr*) &client_addr, &len);

    printf("Client socket port is %d\n", ntohs(client_addr.sin_port));

    close(client_socket);
}
