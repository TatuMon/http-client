#ifndef CONN
#define CONN

#include <stdio.h>
typedef int FileDesc;

FileDesc establishConnection(const char* target_address, const char *port);

#endif
