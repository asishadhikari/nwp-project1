#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <pthread.h>
#include<stdint.h>

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


ssize_t Writeline(int fd, void *vptr, size_t n) {
    size_t      nleft;
    ssize_t     nwritten;
    char *buffer;

    buffer = vptr;
    nleft  = n;
    while ( nleft > 0 ) {
	if ( (nwritten = write(fd, buffer, nleft)) <= 0 ) {
	    if ( errno == EINTR )
		nwritten = 0;
	    else
		return -1;
	}
	nleft  -= nwritten;
	buffer += nwritten;
    }

    return n;
}





void capitalize(char *buf, int soc){
	uint32_t i = 0;
	char c, nl = '\n';
	Readline(soc,buf,MAX_LINE);
	//buffer contains user's string
	while( (c = buf[i]) != '\n' && i < MAX_LINE-1){
		if( c >= 'a' && c <= 'z'){
    		c = c - ('a' - 'A');
			buf[i] = c;
		}
		i++;
	}
	Writeline(soc, &i, sizeof(i));
	Writeline(soc, &nl, sizeof(nl));
	Writeline(soc, buf, i+1);

}
void send_file(char *buf, int soc){
	char c, *message = "NOT FOUND", nl = '\n';
	FILE *fp;
	uint32_t num_bytes = 0;
	//read in file name
	Readline(soc, buf, MAX_LINE-1);
	//sanitise buffer to just contain the provided file name
	for (int i = 0; i < strlen(buf); i++){
		c = buf[i];
		if (c == '\n' || c == '\r'){
			buf[i] = 0;
		}	

	}	
	if( (fp = fopen(buf,"rb")) ==NULL){
		//no such file present and assuming buffer is large enough for mesg
		num_bytes = strlen(message);
		Writeline(soc,&num_bytes,sizeof(num_bytes));
		Writeline(soc,&nl,sizeof(nl));
		Writeline(soc,message,num_bytes);
		return;
	}else{
		int done = 0;
		fseek(fp,0,SEEK_END);
		//get file size
		size_t file_len = ftell(fp);
		//reset to head 
		fseek(fp,0,SEEK_SET);
		
		if (MAX_LINE >= file_len){
			fread(buf,1, file_len,fp);
			num_bytes = file_len;
			Writeline(soc, &num_bytes,sizeof(num_bytes));
			Writeline(soc,&nl,sizeof(nl));
			Writeline(soc,buf,num_bytes);	
		}else{
			
		}

	}


}
