/**********************************************************************
name:
	prog.c -- execute a program for tiny shell
history:
	3/99	- initial version
	10/99	- new interfaces for greater clarity
**********************************************************************/

#include "tsh.h"
#include <unistd.h>

/********************************************************************
exec_program:
	Execute a program per argv[0..argc-1] and redirect[0..1].
	Return exit status.
********************************************************************/

int exec_program (int argc, char *argv[], char *redirect[]) { 

	/* declare variables */
	
	pid_t child;	/* child process pid or 0 */
	int status;		/* child process exit status */

	/* fork into child and parent processes */
	
	fflush (stdout);

	if ((child = fork ()) == 0) {

		/* this is the child: overlay with argc/argv program */
		
		trace ("*prog child: parent=%d, me=%d\n", getppid (), getpid ());
		trace ("*prog child: execvp with filename=%s\n", argv[0]);
		
		if (redirect[0] != NULL) redirect_stdin  (redirect[0]);
		if (redirect[1] != NULL) redirect_stdout (redirect[1]);

		argv[argc] = NULL;
		execvp (argv[0], argv);
		
		die ("can't execvp %s", argv[0]);

	} else {

		/* this is the parent: wait for child to end */
		
		trace ("*prog parent: me=%d, child=%d\n", getpid (), child);
		trace ("*prog parent: waiting ...\n");
		
		wait (&status);
		
		trace ("*prog parent: ... wait done; child status=%d\n", status);
	
	} /* TODO: check for fork failure */

	/* return child exit status */
	
	return status;

}


