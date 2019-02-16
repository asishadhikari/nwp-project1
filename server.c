#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "helper.h"

#define MAX_LINE 1000    	

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void error(char* msg){
	perror(msg);
	exit(EXIT_FAILURE);

}

int main(int argc, char** argv){		
	int       list_s;                /*  listening socket          */
	int       conn_s;                /*  connection socket         */
	short int port;                  /*  port number               */
	struct    sockaddr_in servaddr;  /*  socket address structure  */
	struct    sockaddr_in claddr;	 /* used for populating client info*/ 	 
	char      buffer[MAX_LINE];      /*  character buffer          */
	char     *endptr;                /*  error checking for strtol()  */


	if (argc!=2){
		errno = EINVAL;
		error("usage: ./server PORT_NO\n");
	}
	else{
		port = strtol(argv[1], &endptr, 0);
		if (*endptr){
			error("Invalid port number supplied!");
		}
	}

	//instantiate listening socket used to assign address to socket
	if( list_s = socket(AF_INET, SOCK_STREAM, 0) < 0 ){
		error("No Socket obtained from the OS\n");
	}

	//zero out the sockaddr_in 
	memset(&servaddr, 0, sizeof(servaddr));
	//setup
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl (INADDR_ANY);  //bind to all available interfaces
	servaddr.sin_port = htons(port);

	if( bind( list_s, &servaddr, sizeof(servaddr) ) < 0 ){
		error("Unable to bind the listening socket\n");
	}


	//listen marks a socket as passive socket which  will only be used to accept incoming requests using accept
	//only one socket can listen on a port
	if( listen(list_s,LISTEN_QUEUE) < 0 ){
		error("Error Calling Listen \n");
	}

	while(1){
		if( conn_s = accept(list_s, claddr, sizeof(claddr)) < 0 ){
			error("unable to accept incoming connection\n");
		}
		//spawn a thread for each new incoming connection
	}



	return 0;
}
