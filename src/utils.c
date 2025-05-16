#include "utils.h"
#include "stdio.h"
#include "stdlib.h"

void exit_err(const char *error_msg) {
    fprintf(stderr, "%s", error_msg);
    exit(EXIT_FAILURE);
}

void syscall_err(const char* syscall) {
    perror(syscall);
    exit(EXIT_FAILURE);
}
