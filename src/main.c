#include "conn.h"
#include "sys/socket.h"
#include "utils.h"
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        exit_err("Must provide target IPv4 address");
    }

    const char* target_ipv4 = argv[1];

    FileDesc client_socket = establish_connection(target_ipv4);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    getsockname(client_socket, (struct sockaddr*) &client_addr, &len);

    printf("Port is %d\n", ntohs(client_addr.sin_port));
}
