/**********************************************************************
name:
	parse.c -- parse command line for tiny shell
history:
	3/99	- initial version (RCR)
	10/99	- new interfaces for greater clarity (RCR)
**********************************************************************/

#include "tsh.h"
#include <ctype.h>

/**********************************************************************
helper routines, variables, and defines
**********************************************************************/

static int  set_redirect (char *redirect[], int fd); /* eat filename */
static char backslash (char c); /* convert c to \c */
static int  oops (char *message, int value); /* returns ERR_DONE */

static char destination[MAX_LENGTH];  	/* where to put arguments */

static void get_token   ();	 			/* scan routines ...       */
static void get_string 	(char quote);	/* each routine uses/sets  */
static void get_word 	(char first);	/* the following variables */

static int kind;	/* what get_token found (see enum below) */
static char *arg;	/* first char of last copied argument (kind == ARG) */
static char *cp;	/* where scan should get next char  */
static char *dp;	/* where scan should put next char of an argument */


/*
As a command is scanned, the arguments are copied into destination area.
Entries in argv are set to point into the destination area.
 
Diagram for parsing a typical case:

	offset:			0	1	2	3	4	5	6	7	8	9	10	11	12
	cmd:				a	a	a			"	b	b	"		\0
	destination:	a	a	a	\0	b	b	\0
	argc:			2
	argv[0]:		destination+0
	argv[1]:		destination+4

Logic:

	The get_ routines move cp left to right (initial value == cmd).
	Argument chars are copied to dp (initial value == destination).
	Arg points to first char in the last copied argument.

Stdin/stdout redirection is handled by setting redirect[0..1]:

	redirect[0]:	argument following <, or null if no <
	redirect[1]:	argument following >, or null if no >
	
*/

/* characters that end a word ... */

#define isbreak(c) (isspace(c) \
					|| (c == '#') \
					|| (c == '<') \
					|| (c == '>') \
					|| (c == '\'') \
					|| (c == '\"') \
					|| (c == '|') \
					|| (c == ';') \
					|| (c == '\0'))

/* backslash equivalences ... */

static char *backout = "\a\t\f\n\r";
static char *backin  = "atfnr";

/* token kinds ... */

enum {ARG, LESS, GREATER, END, PIPE, SEMICOLON, BAD};

/* main parse loop state values ... */

enum {NOT_DONE, OK_DONE, ERR_DONE};

/**********************************************************************
parse_command:
	Parse cmd into argv and into redirect.
	Return argc (0 if errors or empty cmd).
**********************************************************************/

int parse_command (char *argv[], int max_argc, char *redirect[], char *cmd) {

	/* declare variables */

	int i;					/* misc loop index */ 
	int argc = 0;			/* number args found so far */
	int state = NOT_DONE;	/* state of main parse loop */

	/* set argc & argv[0..argc-1] & redirect[0..1] per cmd content */

	cp          = cmd;
	dp			= destination;  assert (MAX_LENGTH >= strlen (cmd));
	redirect[0] = NULL;
	redirect[1] = NULL;

	while (state == NOT_DONE) {

		get_token ();

	   	switch (kind) {
	   
	   	case ARG:
			if (argc < max_argc) argv[argc++] = arg;
			else state = oops ("more than %d args", max_argc);
			break;

		case LESS:
			state = set_redirect (redirect, 0);
			break;

		case GREATER:
			state = set_redirect (redirect, 1);
			break;

		case END:
			state = OK_DONE;
			break;

		case PIPE:
			state = oops ("pipes not supported", 0);
			break;

		case SEMICOLON:
			state = oops ("semicolons not supported", 0);
			break;

		case BAD:
			state = oops ("the error is near column %d", cp-cmd);
			break;

		default:
			die ("internal error - bad kind: %d", kind);

		}

	}

	/* show args and redirect for debug */

	if (state == OK_DONE) {

		for (i = 0; i < argc; ++i) {
			trace ("*parse: argv[%d]='%s'\n", i, argv[i]);
		}
		for (i = 0; i < 2; ++i) {
			if (redirect[i] != NULL) {
				trace ("*parse: redirect[%d]='%s'\n", i, redirect[i]);
			}
		}
	}

	/* return argc, or 0 if errors */

	return (state == OK_DONE ? argc : 0);

}

/**********************************************************************
set_redirect:
	Get next token and set redirect[fd] to it if it is an ARG.
	Return NOT_DONE or ERR_DONE (not ARG or already redirected).
**********************************************************************/

static int set_redirect (char *redirect[], int fd) {
	
	char *which = (fd == 0 ? "stdin" : "stdout");
	
	if (redirect[fd] != NULL) { 
		complain ("can't repeat %s redirection", which);
		return ERR_DONE;
	} else if (get_token (), kind == ARG) {
		redirect[fd] = arg;
		return NOT_DONE;
	} else {
		complain ("bad %s filename", which);
		return ERR_DONE;
	}
	
}

/***************************************************************
get_token:
	Parse one token of any kind starting at cp.
	Copy any arg chars into dp.
	Set kind appropriately; also set arg if kind == ARG.
***************************************************************/

static void get_token () {

	/* declare variables */

	char c;		/* cached *cp */

	/* skip over any leading spaces */

	while (isspace (*cp)) ++cp;

	/* see what kind of arg *cp begins; copy as needed and set kind */

	c = *cp++;
	if (c == '\0' || c == '#') {
		kind = END;
	} else if (c == '<') {
		kind = LESS;
	} else if (c == '>') {
		kind = GREATER;
	} else if (c == '|') {
		kind = PIPE;
	} else if (c == ';') {
		kind = SEMICOLON;
	} else if (c == '\"' || c == '\'') {
		get_string (c);
	} else {
		get_word (c);
	}

}

/***************************************************************
get_word:
	Set kind to ARG and arg to current dp.
	Copy first and a sequence of !isbreak chars to dp.
***************************************************************/

static void get_word (char first) {
		
	kind = ARG; arg = dp;
	
	*dp++ = first;
	while (!isbreak (*cp)) *dp++ = *cp++;
	*dp++ = '\0';

}
	
/***************************************************************
get_string:
	Set kind to ARG and arg to current dp.
	Copy a string to dp.
	The quote is the terminator; if not present set kind to BAD. 
	Backslashes OK and are converted per C conventions (\n etc).
***************************************************************/

static void get_string (char quote) {
	
	arg = dp;
		
	while ((*cp != quote) && (*cp != '\0')) {
		if (*cp != '\\') {
			*dp++ = *cp++;
		} else if (++cp, *cp != '\0') {
			*dp++ = backslash (*cp++);
		}
	}

	*dp++ = '\0';

	if (*cp == quote) {
		++cp;
		kind = ARG;
	} else {
		complain ("unterminated string", "");
		kind = BAD;
	}

}

/***************************************************************
backslash:
	Return \c equivalent for the given c.
	Note that the real shell doesn't do this, but should.
***************************************************************/

static char backslash (char c) {
	
	char *p = strchr (backin, c);
	return (p == NULL) ? c : backout[p-backin];

}

/***************************************************************
oops:
	Complain and return ERR_DONE.
***************************************************************/

static int oops (char *message, int value) {
	
	complain (message, (void *)value);
	return ERR_DONE;

}
