/* Tom Diehl
*  CS360
*  Create dining philosopher problem
*  using IPC facilities. 
*/
#define _BSD_SOURCE 
#define _POSIX_SOURCE
#define _XOPEN_SOURCE


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <unistd.h>
#include <dirent.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EATINGTIME 100
#define NUMPHILOS 5

typedef struct _Philo{
	int chop[NUMPHILOS];
	int eat[NUMPHILOS];
	int think[NUMPHILOS];
}Philo;

Philo *myPtr =  NULL; 
int semID = 0;
int IDarray[NUMPHILOS];


struct sembuf semWait[1] = {{0,-1,0}},
	semSignal[1] = {{0, 1, 0}};


int randomGaussian(int mean, int stddev) { // Randomizer fir eat/sleep times
	int seed = time(NULL);
	srand(seed);
	double mu = 0.5 + (double) mean;
	double sigma = fabs((double) stddev);
	double f1 = sqrt(-2.0 * log((double) rand() / (double) RAND_MAX));
	double f2 = 2.0 * 3.14159265359 * (double) rand() / (double) RAND_MAX;
	if (rand() & (1 << 5)) 
		return (int) floor(mu + sigma * cos(f2) * f1);
	else            
		return (int) floor(mu + sigma * sin(f2) * f1);
}

void getSem(int ID){
	if(semop(semID, semWait, 1) == -1){ 
		perror("semop: semop failed"); 
 		exit(1);
	}
}

void giveSem(int ID){
	semop(semID, semSignal, 1);
}

void thinkFunct(int ID){ //thinking...hmmmm...
	int thinkNum = 0;
	thinkNum = randomGaussian(11 ,7);
	sleep(thinkNum);
	myPtr->think[ID] = myPtr->think[ID] + thinkNum;
	printf("Philo %d is thinking: think total = %d \n", ID, myPtr->think[ID]);
}

void eatFunct(int ID){ // eating...num num num
	int eatNum = 0;
	eatNum = randomGaussian(9 ,3);
	sleep(eatNum);
	myPtr->eat[ID] = myPtr->eat[ID] + eatNum;
	printf("Philo %d is eating: Eat total = %d \n", ID,myPtr->eat[ID]);
	myPtr->chop[ID] = -1;			//put chopsticks back
	myPtr->chop[((ID + 1) % NUMPHILOS)]= -1;
	thinkFunct(ID);
}



void philoFunct(int ID){ // check sem status, eat/sleep or try again
	while(myPtr->eat[ID] < EATINGTIME){
		getSem(ID);
		if((myPtr->chop[ID] == -1) && (myPtr->chop[((ID + 1) % NUMPHILOS)] == -1)){
			myPtr->chop[ID] = ID;			//take chopstick
			myPtr->chop[((ID + 1) % NUMPHILOS)]= ID;
			giveSem(ID);
			eatFunct(ID);
		}
		else{
			giveSem(ID);
		}	
	}
}

void *ShareMalloc(int size){
	int shmID;
	char *returnPtr;
	if((shmID = shmget(IPC_PRIVATE,sizeof(int),(SHM_R|SHM_W))) < 0)  exit(1);
	if(((returnPtr = shmat( shmID,0,0))) == (void *) - 1) exit(1); 
		
	shmctl( shmID, IPC_RMID,(struct shmid_ds *) NULL);
	return(returnPtr);
}

int main(){
	semID = semget(IPC_PRIVATE, 1, S_IRUSR | S_IWUSR); // create sem
	if(semID < 0){					//check for error
		printf("%s\n", strerror(errno));
		exit(1);
	}
	if(semctl(semID,0,SETVAL,1) == -1){		//check for error
		printf("%s\n", strerror(errno));
		exit(1);
	}
	myPtr = ShareMalloc(sizeof(Philo));// create shared mem
	
	for(int i = 0; i < NUMPHILOS; i++){
		myPtr->chop[i] = -1;   //initialize chopsticks
	}
	
	for(int i = 0; i < NUMPHILOS; i++){
		if((IDarray[i] = fork())){
			//Parent-- get 5 pid for children
			printf("ID array[%d] = %d\n",i, IDarray[i]);
		}
		else{
			//child
			philoFunct(i);
			printf("Philo %d has left the table\n",i);
			break;
		}
	}
}
