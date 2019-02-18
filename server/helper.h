/* Helper file
 *
 * Ashish Adhikari
 *
 */

#ifndef HELPER
#define HELPER

#define LISTEN_QUEUE 10000	//limit listen queue backlog 
#define MAX_NUM_CONNECTIONS 10
#define MAX_LINE 1000 

void * threadFunc(void *arg);

ssize_t Readline(int fd, void *vptr, size_t maxlen);
ssize_t Writeline(int fd, void *vptr, size_t maxlen);


#endif

