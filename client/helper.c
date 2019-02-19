#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "helper.h"




void error(const char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

void flush_buffer(char *buffer){
	for (int i = 0; i < BUFFER_SIZE; i++) buffer[i] = '\0';
}


void capString(int soc, char *buf){
	char *cmd = "CAP\n", nl = '\n', c;
	Writeline(soc, cmd, 4);
	Writeline(soc, buf, strlen(buf));
	Writeline(soc, &nl, sizeof(nl));
	flush_buffer(buf);
	int rc = Readline(soc, buf, BUFFER_SIZE);
	//print the response from server
	printf("%d is a number and %d bytes read\n",buf[0],rc );
	/*char c_num_bytes[4];
	for (int i = 0; i < 3; i++){
		printf("%d\n",buf[i]);
		c_num_bytes[i]= buf[i];
	}
	uint32_t num_bytes = (uint32_t) atoi(c_num_bytes);
	printf("Response string was %d\n",(int) num_bytes );*/

	flush_buffer(buf);
	Readline(soc, buf, BUFFER_SIZE);
	printf("The capitalised string is %s\n",buf);
}


void getFile(int soc, char *buffer){
	char *pad = "FILE\n", *temp_buf,  nl = '\n', *endptr;
	int n; 
	Writeline(soc, pad, 5);
	Writeline(soc, buffer, strlen(buffer));
	Writeline(soc, &nl, 1);

	if ( (temp_buf = calloc(BUFFER_SIZE, 1)) == NULL ){
		errno = ENOMEM;
		error("Unable to allocate memory");
	}

	Readline(soc, temp_buf, BUFFER_SIZE);
	char *num_bytes_c = calloc(4,1);
	for (int i = 0; i < 4 ; i++){
		num_bytes_c[3-i] = temp_buf[i];
		printf("%d\n", num_bytes_c[i] );
	}

	uint32_t num_bytes;
	for ( int i = 0 ; i < 4 ; i++ ) {
 	 num_bytes = (num_bytes << 8) | num_bytes_c[i];
	}

	free(num_bytes_c);
	Readline(soc, temp_buf, BUFFER_SIZE);
	//file not found in server
	if (strcmp(temp_buf,"NOT FOUND") == 0){
		printf("\n File not found in server \n");
		flush_buffer(buffer);
	}else{
		FILE *fp;
		buffer[strlen(buffer)-1] = '\0';
		if ( (fp = fopen(buffer, "wb")) == NULL ) 
		error("Unable to open file for writing\n");	
		//?? needs to make sure able to handle mutiple messages 
		flush_buffer(buffer);
		if ( (n = Readfile(soc, buffer, num_bytes)) != num_bytes )
			//error("Expected and received bytes dont match\n");
			printf("%d Expected obtained %d bytes\n",num_bytes,n );
		
		fwrite(buffer, 1 , n, fp);
		flush_buffer(buffer);
		


	}
	free(temp_buf);

}

ssize_t Readfile(int soc, void *vptr, size_t maxlen){
	ssize_t n, rc;
	char c, *buffer;
	buffer = vptr;

	for(n = 0; n < maxlen; n++ ){
		if ( (rc == read(soc, &c ,1 )) == 1 ){
			*buffer++ = c;
			if( c == EOF )
				break;
		}else if(rc == 0){
			if (n==0)
				return 0;
			else
				break;
		}
		else{
			if (errno == EINTR)
				continue;
			printf("%c \n is character, %d is read count\n", c,(uint) rc);
			return -1;
		}
	}
	*buffer = '\0';
	return n;

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


