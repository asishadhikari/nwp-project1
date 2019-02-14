/*
  client.c
  ==========
  Ashish Adhikari, 2019
*/

#include <stdio.h>

#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 1000 		


void error(const char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}



int main(int argc, char **argv){
	int svPort;
	int clSocket;
	struct sockaddr_in servAddr;
	char buffer[BUFFER_SIZE];
    
	char user_input = 't';
	//todo implement a proper cl arg parser
		/* * get and load the proper port number
		   * 
		*/
	if (argc!=3)
	{
		error("Usage: %s hostname port\n");	
	}


	//obtain socket descriptor 
	if ( (clSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		error("ECHOCLNT: Error creating listening socket.\n");
    }

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET
    servAddr.sinport = htons(svPort);


	//loop while input != 'q'
	while (user_input!='q'){
		switch(user_input){
			case 's':
				//TODO implement string handler
				capString();				
				break;
		
			case 'f':
				//TODO implement file handler
				getFile();
				break;
		
			default:
				break;
		}
		printf("Enter 's' (capitalize string), 'f' (receive file), or 'q' (to quit)... (\n" );
		user_input = getchar();
	}

	return 0;
	
}
