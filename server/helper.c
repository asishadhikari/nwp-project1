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
	else if (buf[0]=='F' && buf[1] == 'I'
		 && buf[2]=='L' && buf[3] == 'E')
		return 2;
	return -1;

}


ssize_t Readline(int sockd, void *vptr, size_t maxlen) {
    ssize_t n, rc;
    char    c, *buffer;

    buffer = vptr;

    //attempt to read maxlen num bytes
    for ( n = 1; n < maxlen; n++ ) {
	
	//if successful read of one character
	if ( (rc = read(sockd, &c, 1)) == 1 ) {
	    //increment buffer pointer and store the read byte
	    *buffer++ = c;
	    //loop if newline character encountered
	    if ( c == '\n' )
		break;
	}
	
	//if no character was read
	else if ( rc == 0 ) {
	    //if  in first iteration of reading 
	    if ( n == 1 )
		return 0;  //no data ever available in the socket
	    else
		break; //finished reading all data in socket
	}

	else {
	    if ( errno == EINTR ) //non fatal error 
		continue;
	    return -1; //all other errors 
	}
    }

    *buffer = 0; //load terminating null byte 
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
