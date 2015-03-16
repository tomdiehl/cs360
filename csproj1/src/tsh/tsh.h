/**********************************************************************
name:
	tsh.h -- header for tiny shell
history:
	3/99	- initial version (RCR)
	10/99	- new interfaces for greater clarity (RCR)
**********************************************************************/

/* standard includes ... */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "misc.h"

/* defines ... */

#define MAX_LENGTH	1024	/* max length of a command line */
#define MAX_ARGC 	50		/* max number of args */
#define PROMPT 		"? "	/* command prompt */
#define ALERT		"! "	/* error message alert */

/* command routines ... */

extern int  get_command     (char *cmd, int max_length);	
extern int  parse_command   (char *argv[], int max_argc, char *redirect[], char *cmd); 
extern int  exec_command    (int argc, char *argv[], char *redirect[]); 
extern int  exec_program    (int argc, char *argv[], char *redirect[]);
extern void redirect_stdin  (char *filename); 
extern void redirect_stdout (char *filename); 

/* misc routines (see misc.c for details) ... */

extern int  complain   (char *message, void *value); /* returns 0 */
extern int  verify     (char *argv[], int argc, int min, int max);
extern void initialize (int argc, char *argv[]);

/* debugging and other flags (initialized in main.c) ... */

extern int  debug;
extern int  echo;
extern char *version;

#define trace if (debug) printf
