#define _BSD_SOURCE 
#define _POSIX_SOURCE
#define _XOPEN_SOURCE


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct _Philo{
	int chop[5];
	int eat[5];
	int think[5];
}Philo;

Philo *myPtr =  NULL; 
int semID = 0;



int randomGaussian(int mean, int stddev) {
	double mu = 0.5 + (double) mean;
	double sigma = fabs((double) stddev);
	double f1 = sqrt(-2.0 * log((double) rand() / (double) RAND_MAX));
	double f2 = 2.0 * 3.14159265359 * (double) rand() / (double) RAND_MAX;
	if (rand() & (1 << 5)) 
		return (int) floor(mu + sigma * cos(f2) * f1);
	else            
		return (int) floor(mu + sigma * sin(f2) * f1);
}

void philoFunct(int ID){
	int eatnum = 0;
	if((ID == 0) && (chop[0] == -1) && (chop[1] == -1)){
		eatnum = randomGaussian(9 ,3);
		sleep(eatnum);
		
	}
	
}

void *ShareMalloc(int size){
	int shmID;
	char *returnPtr;
	
	if(	(shmID = shmget(IPC_PRIVATE,sizeof(int),(SHM_R|SHM_W))) < 0)
		exit(1);
		
	if(((returnPtr = shmat( shmID,0,0))) == (void *) - 1)
		exit(1); 
		
	shmctl( shmID, IPC_RMID,(struct shmid_ds *) NULL);
	return(returnPtr);
}

int main(){

	int IDarray[5];
	Philo philo;
	semID = semget(IPC_PRIVATE, 1, S_IRUSR | S_IWUSR);
	myPtr = ShareMalloc(sizeof(philo));

	for(int i = 0; i < 5; i++){
		if(IDarray[i] = fork()){
			//Parent
			printf("ID array[%d] = %d\n",i, IDarray[i]);
		}
		else{
			//child
			philoFunct(i);
			break;
		
		}
		
	}
}
