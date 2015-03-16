#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "getWord.h"

#define MAX_WORDSIZE 50

int main (int argc, char *argv[])
{
	char *prevword;
	char *currentword;
	char pair[2*MAX_WORDSIZE + 2];
	
	int numwords = -1;

	char **hashtable;

	if(argv[1] == NULL) 
		printf("Usage: worrd <filename>\n");

	/*
	else if(argv[1][0] IS INTEGER????????
	*/



	else
	{
	FILE* fd = fopen(argv[1], "r");
	
	prevword = getNextWord(fd);
	currentword = getNextWord(fd);

	while(currentword!=NULL)
	{
		strcpy(pair,prevword);
		//pair = strcat(prevword," ");
		strcat(pair," ");
		strcat(pair,currentword);

	printf("%s\n",pair);	

	hashtable[numwords+1]=pair;

	prevword = currentword;
	currentword = getNextWord(fd);
	}
	}





	return 0;
}
