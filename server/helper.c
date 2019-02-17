#include "helper.h"
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <pthread.h>

char RECEIVE_CLIENT_MESSAGE[MAX_LINE]
char SEND_CLIENT_MESSAGE[MAX_LINE]
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


ssize_t Readline(int fd, void *vptr, size_t maxlen){
	spthread_mutex_lock(&lock);
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
	pthread_mutex_unlock(&lock);
	*buffer = '\0'; //for easy strlen usage
	return n;
}


void * threadFunc(void *arg)

{
	int clSocket = *( (int *) arg) ;
	char m


}
