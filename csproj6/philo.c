#define _BSD_SOURCE 
#define _POSIX_SOURCE
#define _XOPEN_SOURCE


#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

//#include "random.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int IDarray[5];
	int shmID;
	
	
	shmID = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT);
	
	for(int i = 0; i < 5; i++){
		if(IDarray[i] = fork()){
		//Parent
		
		printf("ID array[%d] = %d\n",i, IDarray[i]);
		}
		else{
		//child
		break;
		
		}
		
	}
}
