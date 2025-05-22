#include "conn.h"
#include "sys/socket.h"
#include "utils.h"
#include "netinet/in.h"
#include "stdio.h"
#include "unistd.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        exit_err("Must provide target address");
    }

    const char* port = "80";
    if (argc >= 3) {
        port = argv[2];
    }

    const char* targetAddress = argv[1];

    FileDesc client_socket = establishConnection(targetAddress, port);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    getsockname(client_socket, (struct sockaddr*) &client_addr, &len);

    printf("Client socket port is %d\n", ntohs(client_addr.sin_port));

    close(client_socket);
}
