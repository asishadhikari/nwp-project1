#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <pthread.h>

#include "helper.h"


int parse_command(char* buf){
	if(buf[0]=='C' && buf[1]=='A' && buf[2]=='P')
		return 1;
	if (buf[0]=='F' && buf[1] == 'I'
		 && buf[3]=='L' && buf[4] == 'E')
		return 2;
	return -1;

}


ssize_t Readline(int fd, void *vptr, size_t maxlen){
	ssize_t n, rc;
	char c, *buffer;
	printf("Readline called\n");
	buffer = vptr;

	for (n = 1; n< maxlen; n++ ){

		//successfully read 1 char
		if( (rc == read(fd, &c, 1)) == 1 ){
			*buffer++ = c;
			if(c =='\n')
				break;
		}else if( rc == 0 ){
			if (n ==1 )
				return 0; //no data available
			else
				break; //finished reading 
		}else{
			if ( errno == EINTR)
				continue;
			return -1;  //fatal error
		}

	}
	*buffer = '\0'; //for easy strlen usage
	return n;
}


ssize_t Writeline(int fd, void *vptr, size_t maxlen){

}




void capitalize(char *buf, int soc){


	free(buf);
	printf("Freed\n");
}

void send_file(char *buf, int soc){

}
