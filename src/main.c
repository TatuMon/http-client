#include "conn.h"
#include "getopt.h"
#include "netinet/in.h"
#include "stdio.h"
#include "sys/socket.h"
#include "unistd.h"
#include "utils.h"
#include <stdlib.h>

/**
 * Parse the command's arguments, storing the values in the appropiate pointers.
 * */
void parseCmdArgs(int argc, char **argv, char **targetAddress, char **port,
                  char **body) {
  if (argc < 2) {
    exit_err("Must provide target address");
  }
  *targetAddress = argv[1];

  struct option options[] = {
      {"port", required_argument, 0, 'p'},
      {"body", optional_argument, 0, 'b'},
      {0, 0, 0, 0},
  };
  const char *optstring = "p:b:";

  while (1) {
    int option_index = 0;
    char c = getopt_long(argc, argv, optstring, options, &option_index);

    if (c == -1) {
      break;
    }

    switch (c) {
    case 'p':
      *port = optarg;
      break;
    case 'b':
      *body = optarg;
      break;
    }
  }

  return;
}

int main(int argc, char **argv) {
  char *targetAddress = NULL;
  char *port = NULL;
  char *body = NULL;
  parseCmdArgs(argc, argv, &targetAddress, &port, &body);

  // Set default values
  if (port == NULL) {
    port = "80";
  }

  FileDesc client_socket = establishConnection(targetAddress, port);

  struct sockaddr_in client_addr;
  socklen_t len = sizeof(client_addr);
  getsockname(client_socket, (struct sockaddr *)&client_addr, &len);

  printf("Client socket port is %d\n", ntohs(client_addr.sin_port));

  close(client_socket);
}
