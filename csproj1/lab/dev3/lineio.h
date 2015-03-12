#ifndef LINEIO_H
#define LINEIO_H

#define NULL_CHAR	'\0'
#define NEW_LINE	'\n'

/* read a line of text from standard in, store it in s 		*/
/* does not check that the line fits in s 			*/
/* returns 0 if an immediate EOF is detected, 1 otherwise 	*/

int getline(char *s);

/* write string s to standard out followed by a newline		*/

void putline(const char *s);

#endif
