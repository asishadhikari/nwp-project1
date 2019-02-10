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
	int clPort;
	int clSocket;
	struct sockaddr_in servAddr;
	char buffer[BUFFER_SIZE];
    



	char user_input = 't';
	if (argc!=3)
	{
		error("Usage: %s hostname port\n");
	
	}

	//obtain socket descriptor 


	//loop while input != 'q'
	while (user_input!='q'){
		switch(user_input){
			case 's':
				break;
		}
		
		user_input = getchar();

	}

	return 0;
	
}
