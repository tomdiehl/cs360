/**********************************************************************
name:
	misc.c -- miscellaneous routines for tiny shell
history:
	3/99	- initial version (RCR)
	10/99	- new interfaces for greater clarity (RCR)
**********************************************************************/

#include <stdarg.h>
#include <errno.h>
#include "tsh.h"

char *myname = 0;

/*********************************************************************
die: report error to stderr then exit ...
         - fprint "myname: " if myname is not null (hint: set to argv[0])
         - fprintf args
         - print \n (if not in format)
         - print errno message (if not 0)
         - exit with code == 1
     - example: (fp != NULL) || die ("can't open %s", fname);
*********************************************************************/

int die (char *format,...)
{

        va_list args;

        va_start (args, format);

        if (myname != NULL) {
                fprintf (stderr, "%s: ", myname);
        }

        vfprintf (stderr, format, args);

        if (strchr (format, '\n') == NULL) {
                fprintf (stderr, "\n");
        }

        if (errno != 0) {
                fprintf (stderr, "-- error condition: (%s)\n",
                                 strerror (errno));
        }

        va_end (args);

        exit (1);

        return (1);                                     /* make compiler happy */

}

/***************************************************************
initialize: 
    Process switches and set extern variables.
	Called from main.
***************************************************************/

void initialize (int argc, char *argv[]) {

	int i;

	for (i = 1; i < argc; ++i) {
		
		if (strcmp (argv[i], "-d") == 0) {
			debug = 1;
		} else if (strcmp (argv[i], "-e") == 0) {
			echo = 1;
		} else if (strcmp (argv[i], "-v") == 0) {
			printf ("%s: version %s\n", argv[0], version);
		} else {
			die ("usage: %s [-d] [-e] [-v]\n", argv[0]);
		}
	
	}

}

/***************************************************************
complain:
	First, fprintf the ALERT string to stdout. 
    Then do this: fprintf (stdout, message, value).
	Also print a period and a newline.
	Return 0.
***************************************************************/

int complain (char *message, void *value) {
	
	fprintf (stdout, ALERT);
	fprintf (stdout, message, value);
    fprintf (stdout, ".\n");
	return 0;

}

/***************************************************************
verify: 
    Check that min <= argc <= max; return 1 if true.
	If not, complain mentioning argv[0] and return 0.
***************************************************************/

int verify (char *argv[], int argc, int min, int max) {
	
	if (min <= argc && argc <= max) {
		return 1;
	} else {
		complain ("wrong number args for %s", argv[0]);
		return 0;
	}

}
