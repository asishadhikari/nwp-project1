/*
  client.c
  ==========

  Ashish Adhikari, 2019
*/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#define BUFFER_SIZE 1000 		


void error(const char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}



int main(int argc, char *argv[]){
	char *svIP;
	int svPort;
	int clSocket;
	struct sockaddr_in servAddr;

	char buffer[BUFFER_SIZE];
    
	char user_input = 't';
	if (argc!=3){
		errno = EINVAL;
		error("Usage: %s hostname port\n");	
	}

	svIP = argv[1];

	//obtain socket descriptor 
	if ( (clSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) 
		error("ECHOCLNT: Error creating listening socket.\n");
    
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(svPort);
    if( !(inet_aton(svIP, &servAddr.sin_addr)) ){
    	errno = EINVAL;
    	error("Invalid Ipv4 address provided.");
    }

	//loop while input != 'q'
	while (user_input!='q'){
		switch(user_input){
			case 's':
				//TODO implement string handler
//				capString();				
				break;
		
			case 'f':
				//TODO implement file handler
//				getFile();
				break;
		
			default:
				break;
		}
		printf("Enter 's' (capitalize string), 'f' (receive file), or 'q' (to quit)... (\n" );
		user_input = getchar();
	}

	return 0;
	
}
