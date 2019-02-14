#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MAX_LINE 1000    	

void error(char* msg){
		perror(msg);
		exit(EXIT_FAILURE);

}

int main(int argc, char** argv){
		int       list_s;                /*  listening socket          */
		int       conn_s;                /*  connection socket         */
		short int port;                  /*  port number               */
		struct    sockaddr_in servaddr;  /*  socket address structure  */
		char      buffer[MAX_LINE];      /*  character buffer          */
		char     *endptr;                /*  error checking for strtol()  */


		if (argc!=2){
				errno = EINVAL;
				error("usage: ./server PORT_NO\n");
		}
		else{
				port = strtol(argv[1], &endptr, 0);
				if (*endptr){
						//endptr not null means error
						errno = EINVAL;
						error("Invalid port number supplied!");
				}
		}
		
		if( conn_s = socket(AF_INET, SOCK_STREAM, 0) < 0 ){
			errorno = ENOSR;
			error("No Socket obtained from the OS\n");
		}

		return 0;
}
