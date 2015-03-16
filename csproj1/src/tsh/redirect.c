/**********************************************************************
name:
	redirect.c -- redirect stdin/stdout routines for tiny shell
history:
	3/99	- initial version
	10/99	- new interfaces for greater clarity
**********************************************************************/

#include "tsh.h"
#include <unistd.h>
#include <fcntl.h>

/**********************************************************************
redirect routines:
	Close and then reopen file descriptor 0 or 1.
	Die if errors.
**********************************************************************/

void redirect_stdin (char *filename) {
	
	int fd; /* new file descriptor */
	
	trace ("*redirect: new stdin=%s", filename);
	
	close (0);
	fd = open (filename, O_RDONLY);
	
	if (fd != 0) die ("can't open %s as stdin", filename);

}

void redirect_stdout (char *filename) {
	
	int fd; /* new file descriptor */
	
	trace ("*redirect: new stdout=%s", filename);
	
	close (1);
	fd = open (filename, O_WRONLY|O_TRUNC|O_CREAT, 0666);
	
	if (fd != 1) die ("can't open %s as stdout", filename);

}
