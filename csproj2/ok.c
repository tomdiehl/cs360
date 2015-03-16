/*  Tom Diehl
*   CS360 
*   Assignment 2
*   2-7-15
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

#define WORDSIZE 16

int ok(int fd, char *inWord){
    int size = lseek(fd,0 ,SEEK_END);
    int up = size/WORDSIZE;
    int low = 0;
    char dicWord[WORDSIZE];
	
    for(int i = strlen(inWord); i < WORDSIZE - 1; i++){
      inWord[i] = ' ';
    }

    inWord[16] = '\0';
    while(up >= low){
        int index =(up + low)/2;

	lseek(fd, index*WORDSIZE,SEEK_SET);
	read(fd, dicWord,WORDSIZE);
	dicWord[WORDSIZE-1] = '\0'; 
	if(strcmp(inWord,dicWord) < 0) up = index-1;
	else if(strcmp(inWord,dicWord) > 0) low = index+1;
	else if(strcmp(inWord,dicWord) == 0) return 1;
    }
    return 0; 
}	

int main(int argc,char* argv[]){
  char inWord1[WORDSIZE];
  
  int fd = open("webster",O_RDONLY, 0);

  assert( fd > 0 && "Invalid Dictionary"); 
  assert(argv[1]!=NULL && "invalid cmd line argument");

  strcpy(inWord1,argv[1]);
  inWord1[WORDSIZE] = '\0';
  
  int ind = ok(fd,inWord1);
  if(ind == 1)printf("yes\n");
  else printf("no\n");
  return 0;
}

