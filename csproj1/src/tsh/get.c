/**********************************************************************
name:
	get.c -- get a command line for tiny shell
history:
	3/99	- initial version (RCR)
	10/99	- new interfaces for greater clarity (RCR)
**********************************************************************/

#include "tsh.h"

/**********************************************************************
get_command
	Prompt and read command.
	Complain and ignore lines that are longer than max_length.
	Display the command, if echo on.  
	Return 0 if eof.
**********************************************************************/

int get_command (char *cmd, int max_length) {

	/* declare variables */
	
	int eof;	/* end of file? */
	int c;		/* fgetc result */

	/* prompt the user for a command */
	
	fputs (PROMPT, stdout);

	/* read one line into cmd area */
	
	eof = (fgets (cmd, max_length, stdin) == NULL);
	if (!eof) trace ("*get: cmd=%s", cmd);

	/* display command on stdout if echo is on */

	if (!eof && echo) fputs (cmd, stdout);

	/* complain and ignore line if command was truncated */
	
	if (!eof && (cmd[strlen (cmd) - 1] != '\n')) {
		complain ("line longer than %d chars", (void *)max_length);
		while ((c = fgetc (stdin)) != EOF && c != '\n') /* ignore c */ ;
		cmd[0] = '\0';
	}

	/* return with true if not eof */
	
	return !eof;

}
