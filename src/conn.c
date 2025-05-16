#include "conn.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "utils.h"
#include "stdio.h"
#include "assert.h"

const int TCP_PROTOCOL = 6; // Got from greping /etc/protocols

struct sockaddr_in sockaddr_from_host(const char* host, int port) {
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = port;

    if (inet_aton(host, &sockaddr.sin_addr) < 1) {
        syscall_err("inet_aton");
        exit_err("host address not valid");
    }

    return sockaddr;
}

FileDesc establish_connection(const char* target_address) {
    FileDesc sock = socket(AF_INET, SOCK_STREAM, TCP_PROTOCOL);
    if (sock < 0) {
        syscall_err("socket");
    } 

    struct sockaddr_in client_addr = sockaddr_from_host("0.0.0.0", 0);
    if (bind(sock, (struct sockaddr*) &client_addr, sizeof(client_addr)) < 0) {
        syscall_err("bind");
    }


    struct sockaddr_in target_addr = sockaddr_from_host(target_address, 80);

    printf("Establishing connection to %s on port %d\n", target_address, target_addr.sin_port);

    if (connect(sock, (struct sockaddr*) &target_addr, sizeof(target_addr)) < 0) {
        syscall_err("connect");
    }

    printf("Connection established successfuly\n");

    return sock;
}
