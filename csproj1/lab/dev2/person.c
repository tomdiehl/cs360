#include "person.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*	person.c

  Implementation of person-related procedures.

  Author: Dick Lang

  */


Person* personNew(char* name,
				  Person* theFather,
				  Person* theMother) {

	Person* newPerson;		/* holder for the person we create */

	assert(name != NULL);	/* there must be a name */

	/* allocate memory for the person and check for success */
	newPerson = (Person*) malloc(sizeof(Person));
	assert(newPerson != NULL);

	/* initialize all the fields of the person */
	newPerson->name = strdup(name);		/* get our own copy of the name */
	newPerson->father = theFather;
	newPerson->mother = theMother;
	newPerson->spouse = NULL;

	return newPerson;
}


void personDelete(Person* someone) {

	assert(someone != NULL);

	if (someone->name != NULL) free(someone->name);
	free(someone);

	return;
}


void personMarry(Person* theHusband,
				 Person* theWife) {

	assert(theHusband != NULL && theHusband->spouse == NULL);
	assert(theWife != NULL && theWife->spouse == NULL);

	theHusband->spouse = theWife;
	theWife->spouse = theHusband;

	return;
}


void personDivorce(Person* theHusband,
				   Person* theWife) {

	assert(theHusband != NULL && theHusband->spouse == theWife);
	assert(theWife != NULL && theWife->spouse == theHusband);

	theHusband->spouse = theWife->spouse = NULL;

	return;
}
