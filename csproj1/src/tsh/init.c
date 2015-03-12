
#include "tsh.h"
#include <stdlib.h>

/* global variables without "extern" ... */

char cmd[MAX_CMDSIZE];	/* command line area */
char* argv[MAX_NARGS];	/* args found in cmd */
int argc;				/* number of args found */
char* new_stdin;		/* filename of new stdin or NULL */
char* new_stdout;		/* filename of new stdout or NULL */
int pipe_index;			/* if not 0, | before argv[pipe_index] */


int initialize ()
{

/* declare variables */

	int i;

/* set each argv[0..MAX_NARGS-1] to an area MAX_ARGSIZE long */

	for (i = 0; i < MAX_NARGS; i++) {
		argv[i] = (char *) malloc (MAX_ARGSIZE);
	}

/* return true */

	return 1;

}
