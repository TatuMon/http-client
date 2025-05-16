#ifndef UTILS
#define UTILS

// Prints error_msg to stderr and calls exit, terminating the process
void exit_err(const char* error_msg);

// Calls perror(syscall) and calls exit, terminating the process
void syscall_err(const char* syscall);

#endif
