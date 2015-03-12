#include "lineio.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int getline(char* s) {

	char c;                	/* holds current character */
	char* firstChar = s;	/* keeps a pointer to the beginning of the string */

	assert(s != NULL);	/* nothing can work if we are handed a NULL pointer */

	/* loop storing incoming characters until an EOF or new line is detected */

	while (c = getchar(), (c != EOF) && (c != NEW_LINE)) {
		*s++ = c;
	}

	/* if nothing was stored and the first and only character was EOF, return 0 */

	if (s == firstChar && c == EOF) {
		return 0;
	}

	/* otherwise, terminate the string and return 1 */

	*s = NULL_CHAR;
	return 1;
}


void putline(const char* s) {

	/* if handed no string, do nothing and return */

	if (s == NULL) {
		return;
  	}

	/* loop writing out characters until the end of string is detected */

	while (*s != NULL_CHAR) {
		putchar(*s++);
  	}

	/* once the null character is detected, write out a new line and return */

	putchar(NEW_LINE);
	return;
}
