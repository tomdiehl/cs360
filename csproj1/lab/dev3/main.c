/*

	Print the most popular line from stdin

*/

#include <stdio.h>
#include <string.h>
#include "lineio.h"
#include "dict.h"

#define MAXLINE 		1024
#define DICTIONARY_SIZE		731

int main(int argc, char* argv[]) {

	char curText[MAXLINE];		/* stores the line just read */
	char maxText[MAXLINE];          /* stores the line with the maximum count */

	int curCount;			/* count for the current line */
	int maxCount = -1;		/* maximum count detected */

	Dictionary* d = dictionaryNew(DICTIONARY_SIZE);

	while (getline(curText)) {

		/* update the dictionary with this string */

		curCount = dictionaryUpdate(d, curText);

		/* if this string has the highest count so far, copy it and its */
		/* count into the max variables */

		if (curCount > maxCount) {
 			strcpy(maxText,curText);
			maxCount = curCount;
   		}
	}

	if (maxCount > 0) {
		putline(maxText);
  	}

	return 0;
}
