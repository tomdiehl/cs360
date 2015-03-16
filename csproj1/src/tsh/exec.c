/**********************************************************************
name:
	exec.c -- execute a command for tiny shell
history:
	3/99	- initial version
	10/99	- new interfaces for greater clarity
**********************************************************************/

#include "tsh.h"

/*******************************************************************
exec_command
	Execute a single command per argv[0..argc-1] and redirect[0..1].
	Command is built-in or a program.
	Return 1 (0 if command was "exit").
********************************************************************/

int exec_command (int argc, char *argv[], char *redirect[]) {

	/* declare variables */
	
	int result;	/* final result: 0 if exit, 1 if continue */ 
	int status;	/* exit status of child program */ 

	/* execute the command and set result */
	
	result = 1;
	if (argc <= 0) { /* empty command */
		trace ("*exec: empty command\n");

	} else if (strcmp (argv[0], "exit") == 0) { /* exit */
		trace ("*exec: exit command\n");
		result = 0;

	} else if (strcmp (argv[0], "cd") == 0) { /* cd */
		trace ("*exec: cd command\n");
		if (verify (argv, argc, 1, 2)) {
			if (argc == 1) argv[1] = getenv ("HOME");
			if (chdir (argv[1]) < 0) complain ("can't cd to %s", argv[1]);
		}

	} else { /* a program to execute */
		trace ("*exec: program command ...\n");
		status = exec_program (argc, argv, redirect);
		trace ("*exec: ... program command done.\n");
	}

	/* return result */
	
	return result;

}
