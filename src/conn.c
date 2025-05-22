#include "conn.h"
#include "assert.h"
#include "netdb.h"
#include "netinet/in.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "utils.h"
#include "unistd.h"

const int TCP_PROTOCOL = 6; // Got from greping /etc/protocols

void addrInfoFromHost(const char *host, const char *port,
                      struct addrinfo **results) {
  struct sockaddr_in sockaddr;

  struct addrinfo addrFilter = {.ai_family = AF_UNSPEC,
                                .ai_socktype = SOCK_STREAM,
                                .ai_protocol = TCP_PROTOCOL};

  int gai = getaddrinfo(host, port, &addrFilter, results);
  if (gai != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai));
    exit(EXIT_FAILURE);
  }
}

// Try to establish a connection using the collection of addrinfo provided by
// addresses
//
// On a successful call, `connectedSockAddr` gets populated with the sockaddr of
// the addrinfo used to connect
//
// @return FileDesc Target's socket file descriptor. In case of error, -1 is returned.
FileDesc tryConnect(struct addrinfo **addresses) {
  struct addrinfo *currAddrInfo;

  for (currAddrInfo = addresses[0]; currAddrInfo != NULL; currAddrInfo = currAddrInfo->ai_next) {
    FileDesc sock = socket(currAddrInfo->ai_family, currAddrInfo->ai_socktype, currAddrInfo->ai_protocol);
    if (sock == -1) {
      syscall_err("socket");
    }

    if (connect(sock, currAddrInfo->ai_addr, currAddrInfo->ai_addrlen) == 0) {
      freeaddrinfo(currAddrInfo);
      return sock;
    }

    close(sock);
  }

  return -1;
}

// @return FileDesc Retorna el socket del cliente (localhost)
FileDesc establishConnection(const char *target_address, const char *port) {
  FileDesc sock = socket(AF_INET, SOCK_STREAM, TCP_PROTOCOL);
  if (sock < 0) {
    syscall_err("socket");
  }

  struct addrinfo **targetPossibleAddresses;
  addrInfoFromHost(target_address, port, targetPossibleAddresses);

  if (tryConnect(targetPossibleAddresses) == -1) {
    exit_err("failed to connect");
  }

  printf("Connecting to %s on port %s\n", target_address, port);
  printf("------------------------------------\n");
  printf("Connection established successfuly\n");

  return sock;
}
