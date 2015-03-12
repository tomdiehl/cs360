/**********************************************************************
*  name:                                                              *
*     misc.h -- CS 360 miscellaneous routines                         *
*  synopsis:                                                          *
*     #include <cs360/misc.h>                                         *
*     cc ... -lcs360                                                  *
*  description:                                                       *
*      See lecture notes.                                             *
*  author:                                                            *
*     Roger Ray, WSUV CS 360, Sep 1999                                *
**********************************************************************/

#ifndef _CS360_MISC_H
#define _CS360_MISC_H

/* debugging and error handling */

extern void see (char *format, ...);
extern int  die (char *format, ...);
extern char *myname;

#endif
