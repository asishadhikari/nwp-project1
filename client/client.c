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
#include <stdint.h>
#include <unistd.h>
#include "helper.h"

char buffer[BUFFER_SIZE];


int main(int argc, char *argv[]){
	char *svIP, *svPort, *endptr;
	int clSocket, port;
	struct sockaddr_in servAddr;

	char user_input = 't';
	if (argc!=3){
		errno = EINVAL;
		error("Usage: %s hostname port\n");	
	}

	//obtain socket descriptor 
	if ( (clSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) 
		error("ECHOCLNT: Error creating listening socket.\n");
    

	svIP = argv[1];
	svPort = argv[2];

	port = strtol(svPort, &endptr,10);
	if(*endptr)
		error("Invalid port");
	
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    //assign IP address
    if( !(inet_aton(svIP, &servAddr.sin_addr)) ){
    	errno = EINVAL;
    	error("Invalid Ipv4 address provided.");
    } 

    //attempt to connect
    if ( ( connect(clSocket, (struct sockaddr*) &servAddr, sizeof(servAddr)) ) < 0 )
    	error("Unable to call connect");
    printf("Connected to server\n");

    char *cap = "CAP\n" , nl = '\n', to_cap;
    uint32_t str_len = 0;
	//loop while input != 'q'
	char trash;
	while (user_input!= 'q'){
		printf("\n\tEnter 's' (capitalize string), 'f' (receive file), or 'q' (to quit)... (\n" );
		user_input = (char) getc(stdin);
		trash = getc(stdin); //get rid of newline character
		flush_buffer(buffer);
		switch(user_input){
			case 's':
				printf("\nEnter the string to capitalise\n");
				fgets(buffer, BUFFER_SIZE,stdin);
				capString(clSocket,buffer);
				break;
			case'f':
				printf("\nEnter the file name you want from server\n");
				fgets(buffer, BUFFER_SIZE, stdin);
				getFile(clSocket, buffer);
				break;
		}
		if(user_input=='q')
			break;
		printf("Press enter to get the menu items again...\n");
		//consume all irrelevant data in user input
		while ( (trash = (char) getc(stdin)) != '\n');
	}
	close(clSocket);

	return 0;
	
}
