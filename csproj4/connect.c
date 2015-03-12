/*
*	Tom Diehl
*	CS360
*	Connect.c
*/	


#define _BSD_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <assert.h>


#define MAXCOLON  10
#define DEBUG 1


void pipeFunct(int count, char* input[]){	
	int fd[2];  	//File descriptors
	int rdr, wrt;	
	int numColon = 0;			// number of programs		
	int colonPos[MAXCOLON];		//array of colon indexes
	
	colonPos[0]= 0; 
	
	assert(pipe(fd) >= 0);		// fd[0] and fd[1] = read , write 	
	
	for(int i = 0; i < count; i++){
		if(!(strcmp(input[i],":"))){
			input[i] = NULL;
			numColon++;			
			colonPos[numColon] = i +1;
			if(i == 0){
				fprintf(stderr, "cmd must start with program name\n");
				exit(0);
			}
			if(input[i+1] == NULL){
				fprintf(stderr, "cmd must end with program name\n");
				exit(0);
			}
		}
	}
	
	for(int i = 1; i < numColon +1; i ++){
		pipe(fd);
		rdr = fd[0];
		wrt=fd[1];
		if(fork()){
		//Parent
			input = input + colonPos[i] - colonPos[i-1];
			close(wrt);
			close(0); dup(rdr); close(rdr);    //redirect input
		}
		else {
		//Child
			close(rdr);
			close(1); dup(wrt); close(wrt);		//redirect output;
			if(DEBUG) printf("child argv[%d] = %s\n",i, input[i]);
			execvp (input[0], input);	
			fprintf(stderr, "%s: exec of child failed\n",input[i]);	
		}
	}
	execvp(input[0], input);
}


int main(int argc, char *argv[]){

	argc--;			//Skip prog name
	argv++;

	pipeFunct(argc,argv);
	return 0;	
}

