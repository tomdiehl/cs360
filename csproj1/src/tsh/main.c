/**********************************************************************
name:
	main.c -- main module for tiny shell
history:
	3/99	- initial version
	10/99	- new interfaces for greater clarity
**********************************************************************/

#include "tsh.h"

int  debug 		= 0;		/* display tracing info on stdout? */
int  echo  		= 0;		/* echo command line to stdout? */
char *version 	= "V6b";		/* version number */

/**********************************************************************
main:
	Tiny shell entry point.
	Switches:	-d	turn on debugging
				-e  turn on echoing
				-v	echo version number
**********************************************************************/

int main (int my_argc, char *my_argv[]) {

	/* declare variables */

	char cmd[MAX_LENGTH];	 	/* command line area */
	char *argv[MAX_ARGC+1];		/* args found in cmd & room for NULL */
	int  argc;			        /* number of args found */
	char *redirect[2];			/* stdin/stdout filenames or NULL */
	int  more = 1;		   		/* when 0, command loop ends */

	/* process command line and get ready */

	initialize (my_argc, my_argv);

	/* get, parse, and execute commands until eof or "exit" command */

	while (more && get_command (cmd, MAX_LENGTH)) {
		argc = parse_command (argv, MAX_ARGC, redirect, cmd);
		more = exec_command (argc, argv, redirect);
	}

	/* exit */

	exit (0);

}
