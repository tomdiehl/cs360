/*   Tom Diehl
*    tom.diehl@email.wsu.edu
*    CS 360 assignment 1
*    *Note -- Worked in collaboration with Ben Bachelder
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <getWord.h>
#include <string.h>
#include "hash.h"
#include <ctype.h>

typedef struct _arrayStruc{   //Struct for sorted array
    char *key;
    int *value;       
}arrayStruct;

arrayStruct *myArray = NULL;
int pos = 0;	

void funct(char *key, void *value){  //function for copying nodes into array
    myArray[pos].key = key;
    myArray[pos].value = (int *)value;
    pos++;
}

void freefunct(char *key, void *value){  //function for copying nodes into array
    free((char*) key);
    free((int*)value);
}

static int compare(const void *a, const void *b){ // Compare funct for qsort
    arrayStruct *A = (arrayStruct *) a;
    arrayStruct *B = (arrayStruct *) b;
    return (*(B->value) - *(A->value));
}

void printArray(arrayStruct *myArray,int count,int numPrint){ //funct for printing Array
  int currentP = 0;
  if(numPrint==0){
    numPrint = count;
    }
  while(currentP <= numPrint-1){
    printf("%10d %s \n",*((int *)myArray[currentP].value), myArray[currentP].key);
    currentP++;
  }	
}

int main(int argc, char *argv[]){
  
    char *currWord = NULL;
    char *prevWord = NULL;
    
    HashRoot *ht = hashCreate(50);	
    int numPrint = 0;
    
    for(int i = 1; i < argc; i++){
        if( argv[i][0] == '-'){
	  if(!isdigit(argv[i][1])){
	    fprintf(stderr, "input format not of format -%%d, default value used(10)\n");
	  }
	 else sscanf(argv[1], "-%d", &numPrint );	
	}
	else{
	FILE *fd = fopen( argv[i] ,"r");
	if(fd == 0){
	    fprintf(stderr, "could not open file \n" );
	}
	else{
	    while((currWord = getNextWord(fd)) != NULL){
	      if(prevWord != NULL){
		  char *temp = malloc(strlen(prevWord) + strlen(currWord) + 2 );
		  int *value = malloc(sizeof(int));
		  *value = 1;                
		  strcpy(temp, prevWord);    //combine words into pairs
		  strcat(temp, " ");
		  strcat(temp, currWord);
		  if(!(hashInsert(ht,temp,value))) {  // if insert fails increment value if search finds key
	 	      int *search = hashSearch(ht,temp);
		      (*search)++;
		      free(value);
		      free(temp);
		      free(prevWord);
		      prevWord = currWord;
		  }
		  else{
		      free(prevWord);
		      prevWord = currWord;
		  }
	      }  
	      else{
		  prevWord = currWord;
	      }	 
	    }
	    free(currWord);
	    fclose(fd);
	}
	}
    }
    //Get sorted Array
    myArray = (arrayStruct*) malloc(sizeof(arrayStruct)*ht->count); 
    hashApply(ht,funct);
    qsort(myArray,ht->count,sizeof(arrayStruct),compare);
    
    //Output
    if(numPrint > ht->count){
      fprintf(stderr,"Number elements to print is greater then elements, printing whole table \n");
      numPrint = ht->count;
    }
    printArray(myArray, ht->count,numPrint);    
    
    //Clean up
    free(myArray);                
    hashFree(ht,freefunct);
}

