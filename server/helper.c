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
	pthread_mutex_lock(&lock);
	ssize_t n, rc;
	char c, *buffer;

	buffer = vptr;

	for (n = 1, n< maxlen, n++ ){

		if( (rc== read(fd,) )  )

	}
	
	pthread_mutex_unlock(&lock);

}


void * threadFunc(void *arg)

{
	int clSocket = *( (int *) arg) ;
	char m


}
