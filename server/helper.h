/* Helper file
 *
 * Ashish Adhikari
 *
 */

#ifndef HELPER
#define HELPER

#define LISTEN_QUEUE 10000	//limit listen queue backlog 
#define MAX_NUM_CONNECTIONS 10000
#define MAX_LINE 20

ssize_t Readline(int fd, void *vptr, size_t maxlen);
ssize_t Writeline(int fd, void *vptr, size_t maxlen);
void capitalize(char *buf, int soc);
void send_file(char *buf, int soc);
int parse_command(char* buf);


#endif

