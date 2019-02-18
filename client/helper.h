#ifndef HELPER
#define HELPER

#define BUFFER_SIZE 1000 		

void error(const char* msg);
ssize_t Writeline(int fd, void *vptr, size_t n);
ssize_t Readline(int sockd, void *vptr, size_t maxlen);

#endif