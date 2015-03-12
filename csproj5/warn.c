#define _BSD_SOURCE 
#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>

#define BUFFSIZE 100
	
	int childID;
	int parentID;
	int rdr,wrt;
	char *input;	
	
void al_handler(){
	return;
}
	
void par_handler(){

	signal(SIGINT, SIG_IGN);
	signal(SIGFPE,al_handler);
	char *message = (char*)calloc(sizeof(char),BUFFSIZE);
	printf("Enter Alarm Message:\n");
	fgets(message, BUFFSIZE, stdin);

	write(wrt, message, strlen(message));
	kill(childID, SIGFPE);
}

void child_handler(){
	char *temp= (char*)calloc(sizeof(char),BUFFSIZE);	
	input = (char*)calloc(sizeof(char),BUFFSIZE);	
	read(rdr,input, BUFFSIZE);
	strcpy(temp,input);
	temp[strlen(input)-1] = '\0';
	if(!strcmp(temp,"exit")){
		printf("Child Exiting now\n");
		kill(parentID,SIGKILL);	
		}
}


int main(){
	
	int fd[2];
	
	pipe(fd);
	rdr = fd[0];
	wrt=fd[1];
	
	
	if(fork()){
		//Parent
		parentID=getpid();
		close(rdr);
		while(1){
			signal(SIGINT, par_handler);
			pause();
		}
	}
	else {
		//Child
		childID= getpid();
		signal(SIGINT, SIG_IGN);
		signal(SIGFPE,child_handler);
		close(wrt);
		while(1){
			signal(SIGALRM, al_handler);
			signal(SIGFPE,child_handler);
			alarm(5);
			pause();
			alarm(0);
			if(!(input=='\0'))printf("%s",input);
		}
	}
	return 0;
}

