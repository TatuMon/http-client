#ifndef CONN
#define CONN

#include <stdio.h>
typedef int FileDesc;

FileDesc establish_connection(const char* target_address);

#endif
