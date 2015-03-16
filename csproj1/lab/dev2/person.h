#ifndef PERSON_H
#define PERSON_H

/*	person.h
	
	Definition of person data type and routines to manipulate it


	Author:	Dick Lang

*/

typedef struct _person {
	char* name;					/* name of the person */
	struct _person* father;
	struct _person* mother;
	struct _person* spouse;		/* NULL if no spouse */
} Person;


/* constructor for a new person */

Person* personNew(char* name,
				  Person* theFather,
				  Person* theMother);


/* destructor for person, does not follow pointers */

void personDelete(Person* someone);


/* Implement other relationships */

void personMarry(Person* theHusband,
				 Person* theWife);

void personDivorce(Person* theHusband,
				   Person* theWife);

#endif
