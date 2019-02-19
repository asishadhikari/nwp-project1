#ifndef HELPER
#define HELPER

#define BUFFER_SIZE 100000		

void error(const char* msg);
ssize_t Writeline(int fd, void *vptr, size_t n);
ssize_t Readline(int sockd, void *vptr, size_t maxlen);
void capString(int soc, char *buffer);
void getFile(int soc, char *buffer);
ssize_t Readfile(int soc, char *vptr, size_t maxlen);
void flush_buffer(char *buffer);

#endif