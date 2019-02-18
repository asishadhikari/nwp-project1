#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <pthread.h>

#include "helper.h"

int identify_command

ssize_t Readline(int fd, void *vptr, size_t maxlen){
	ssize_t n, rc;
	char c, *buffer;

	buffer = vptr;

	for (n = 1, n< maxlen, n++ ){

		//successfully read 1 char
		if( (rc == read(fd, &c), 1) == 1 ){
			*buffer++ = c;
			if(c =='\n')
				break;
		}else if( rc == 0 ){
			if (n ==1 )
				return 0;
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


ssize_t Writeline(int fd, void *vptr, ssize_t maxlen){

}



void * threadFunc(void *arg)

{
	int clSocket = *( (int *) arg) ;
	char read_buffer[MAX_LINE]; //buffer to read into 
	//read line once to identify command received
	if ( (i = Readline(clSocket, read_buffer, MAX_LINE)) < = 0)
		error("Unable to read any data from client. \n");
	




	
	


}
