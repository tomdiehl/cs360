/**********************************************************************
*  name:                                                              *
*     dir.h -- CS 360 directory routines                              *
*  synopsis:                                                          *
*     #include <cs360/dir.h>                                          *
*     cc ... -lcs360                                                  *
*  description:                                                       *
*      See Dir1 and Dir 2 lecture notes.                              *
*  author:                                                            *
*     Roger Ray, WSUV CS 360                                          *
**********************************************************************/

#ifndef _CS360_DIR_H
#define _CS360_DIR_H

/* defines and typedefs */

#define MAXPATHSIZE 2000

typedef int Function (char *filename);

/* file and directory manipulation */

extern int  visit (char *directory, Function *f);
extern char *pwd ();
extern int  isDirectory (char *pathname);

#endif
