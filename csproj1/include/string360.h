
/**********************************************************************
*  name:                                                              *
*     string.h -- CS 360 sring routines                               *
*  synopsis:                                                          *
*     #include <cs360/string.h>                                       *
*     cc ... -lcs360                                                  *
*  description:                                                       *
*      See lecture notes.                                             *
*  author:                                                            *
*     Roger Ray, WSUV CS 360, Sep 1999                                *
**********************************************************************/

#ifndef _CS360_STRING_H
#define _CS360_STRING_H

/* string parsing ... */

extern int stringToInteger (char *s, int *n);
extern int stringToWords   (char *v[], int maxN, char *s);
extern int stringToFields  (char *v[], int maxN, char *s, char delimiter);

/* string comparision ... */

extern int stringIsPrefix (char *x, char *y);

#endif
