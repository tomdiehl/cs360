#include "list.h"
#include <stdio.h>

#define FALSE	0
#define TRUE	1


/* main.c

	test program for list functions

	Author: Dick Lang

	*/

 /* routine to duplicate a list (but not the people it points to) */

 List* listCopy(List* list) {

 	List *newList = NULL;
	List *end = NULL;

	while (list != NULL) {
		if (end == NULL) {
			end = newList = listNew(list->first,NULL);
   		} else {
			end->next = listNew(list->first,NULL);
			end = end->next;
   		}

		list = list->next;
	}

	return newList;
 }

 /* routine to test if two lists are identical, with the same order, pointing at the same people */

 int listSame(List* listA, List* listB) {

 	while (listA != NULL) {
  		if (listB == NULL || listB->first != listA->first) {
			return FALSE;
		}
		listA = listA->next;
		listB = listB->next;
	}

	if (listB != NULL) {
		return FALSE;
	}

	return TRUE;
 }


 /* main test routine */

 int main(int argc, char* argv) {

 	int fail = 0;
	List* listA;
	List* listB;
	List* listC;
	List* listD;
	Person* p1;
	Person* p2;
	Person* p3;
	Person* p4;
	Person* p5;
	Person* p6;

	/* make a few people to mess around with */

	p1 = personNew("Charles",NULL,NULL);
	p2 = personNew("Diana",NULL,NULL);
	p3 = personNew("Bismark",NULL,NULL);


	printf("Testing listNew... ");

	/* make a list of the people */

	listA = listNew(p1,NULL);
	listA = listNew(p2,listA);
	listA = listNew(p3,listA);

	/* there should be a list, and each person should be pointed to */

	if (listA == NULL) fail++;
	if (listA->first == NULL || listA->first != p3) fail++;
	if (listA->next == NULL || listA->next->first != p2) fail++;
	if (listA->next->next == NULL || listA->next->next->first != p1) fail++;
 	if (listA->next->next->next != NULL) fail++;

	if (fail) {
		printf("Fails (%i)\n",fail);
	} else printf("OK\n");
	fail = 0;


	printf("Testing listLength... ");

	/* check that the length of an empty list is zero, and that the previous list is three */

	if (listLength(NULL) != 0) fail++;
	if (listLength(listA) != 3) fail++;

	if (fail) {
		printf("Fails (%i)\n",fail);
	} else printf("OK\n");
	fail = 0;


	printf("Testing listWriteNames. Should see Bismark, Diana, Charles...\n");

	/* write out the names, we have to depend on the user to check the order */

	listWriteNames(listA);

	printf("There should be no lines between here...");

	/* writing out an empty list should produce no lines */

	listWriteNames(NULL);

	printf("and here.\n");


	printf("Testing listContainsPerson...");

	/* check that each person is in the list, and check that a person is not in the */
	/* emnpty list. And that the null person is not found in the list or an empty list */

	if (listContainsPerson(listA,p1) == 0) fail++;
	if (listContainsPerson(listA,p2) == 0) fail++;
	if (listContainsPerson(listA,p3) == 0) fail++;
	if (listContainsPerson(NULL,p1) != 0) fail++;
	if (listContainsPerson(listA,NULL) != 0) fail++;
	if (listContainsPerson(NULL,NULL) != 0) fail++;

	if (fail) {
		printf("Fails (%i)\n",fail);
	} else printf("OK\n");
	fail = 0;


	printf("Testing listGetNthPerson... ");


 	/* check that each person is in the expected position in the list */

	if (listGetNthPerson(listA,0) != p3) fail++;
	if (listGetNthPerson(listA,1) != p2) fail++;
	if (listGetNthPerson(listA,2) != p1) fail++;
	if (listGetNthPerson(listA,3) != NULL) fail++;
	if (listGetNthPerson(NULL,0) != NULL) fail++;

	if (fail) {
		printf("Fails (%i)\n",fail);
	} else printf("OK\n");
	fail = 0;


	printf("Testing listConcat... ");

	/* make a new list with new people in it */

	listB = listNew(p4 = personNew("Nero",NULL,NULL),NULL);
	listB = listNew(p5 = personNew("Caesar",NULL,NULL),listB);
	listB = listNew(p6 = personNew("Octavius",NULL,NULL),listB);

	/* check that concatenating an empty list to another list does not change the list */

	listD = listCopy(listA);
	listC = listConcat(listA,NULL);
	if (listC != listA) fail++;
	if (!listSame(listC,listD)) fail++;

	/* check that concatenating a list to an empty list produces the non-empty list */

	listC = listConcat(NULL,listA);
	if (!listSame(listC,listD)) fail++;

	/* check that concatenating an empty list to an empty list results in an empty list */

	if (listConcat(NULL,NULL) != NULL) fail++;

	/* concatenate the new list to the old and check if everyone is in the correct position */

	listC = listConcat(listA,listB);
	if (listC != listA) fail++;
 	if (listGetNthPerson(listA,0) != p3) fail++;
	if (listGetNthPerson(listA,1) != p2) fail++;
	if (listGetNthPerson(listA,2) != p1) fail++;
	if (listGetNthPerson(listA,3) != p6) fail++;
	if (listGetNthPerson(listA,4) != p5) fail++;
 	if (listGetNthPerson(listA,5) != p4) fail++;
	if (listGetNthPerson(listA,6) != NULL) fail++;

	if (fail) {
		printf("Fails (%i)\n",fail);
	} else printf("OK\n");
	fail = 0;


 	printf("Testing listReverse... ");

	/* reverse the list and check everyone's position */

	listB = listCopy(listA);
	listA = listReverse(listA);
 	if (listGetNthPerson(listA,0) != p4) fail++;
	if (listGetNthPerson(listA,1) != p5) fail++;
	if (listGetNthPerson(listA,2) != p6) fail++;
	if (listGetNthPerson(listA,3) != p1) fail++;
	if (listGetNthPerson(listA,4) != p2) fail++;
 	if (listGetNthPerson(listA,5) != p3) fail++;
	if (listGetNthPerson(listA,6) != NULL) fail++;

	/* reverse and check it again */

	listA = listReverse(listA);
 	if (listGetNthPerson(listA,0) != p3) fail++;
	if (listGetNthPerson(listA,1) != p2) fail++;
	if (listGetNthPerson(listA,2) != p1) fail++;
	if (listGetNthPerson(listA,3) != p6) fail++;
	if (listGetNthPerson(listA,4) != p5) fail++;
 	if (listGetNthPerson(listA,5) != p4) fail++;
	if (listGetNthPerson(listA,6) != NULL) fail++;

	/* the list should now be the same as before the two reverses */

	if (!listSame(listA,listB)) fail++;

	/* reverse of the empty list should be the empty list */

	if (listReverse(NULL) != NULL) fail++;

	/* make a single person list, reverse it and check that nothing changed */

	listD = listNew(p1,NULL);
	listC = listCopy(listD);
	listC = listReverse(listC);
	if (!listSame(listC,listD)) fail++;

	if (fail) {
		printf("Fails (%i)\n",fail);
	} else printf("OK\n");
	fail = 0;


	printf("Testing listRemoveLastPerson... ");

	/* removing the last person from an empty list should return an empty list */

	if (listRemoveLastPerson(NULL) != NULL) fail++;

	/* removing the last person from single person list should return the single person */

	listD = listRemoveLastPerson(listC);
	if (!listSame(listC,listD)) fail++;

	/*remove the last person of a longer list and check that he/she is gone and rest of list intact */

	listC = listRemoveLastPerson(listB);
	if (listC->next != NULL) fail++;
	if (listC == NULL || listC->first != p4) fail++;
	if (listLength(listB) != 5) fail++;
 	if (listGetNthPerson(listB,0) != p3) fail++;
	if (listGetNthPerson(listB,1) != p2) fail++;
	if (listGetNthPerson(listB,2) != p1) fail++;
	if (listGetNthPerson(listB,3) != p6) fail++;
	if (listGetNthPerson(listB,4) != p5) fail++;
 	if (listGetNthPerson(listB,5) != NULL) fail++;

 	if (fail) {
		printf("Fails (%i)\n",fail);
	} else printf("OK\n");
	fail = 0;


	printf("Testing listRemoveNthPerson... ");

	/* check that removing the nth person from an empty list results in an empty list */

	if (listRemoveNthPerson(NULL,10) != NULL) fail++;

	/* check that removing a person beyond the end does nothing */

	listC = listRemoveNthPerson(listB,listLength(listB));
	if (listC != NULL) fail++;
	if (listLength(listB) != 5) fail++;
 	if (listGetNthPerson(listB,0) != p3) fail++;
	if (listGetNthPerson(listB,1) != p2) fail++;
	if (listGetNthPerson(listB,2) != p1) fail++;
	if (listGetNthPerson(listB,3) != p6) fail++;
	if (listGetNthPerson(listB,4) != p5) fail++;
 	if (listGetNthPerson(listB,5) != NULL) fail++;

	/* also, check that a negative number for a position has no effect */

	listC = listRemoveNthPerson(listB, -1);
	if (listC != NULL) fail++;
	if (listLength(listB) != 5) fail++;
 	if (listGetNthPerson(listB,0) != p3) fail++;
	if (listGetNthPerson(listB,1) != p2) fail++;
	if (listGetNthPerson(listB,2) != p1) fail++;
	if (listGetNthPerson(listB,3) != p6) fail++;
	if (listGetNthPerson(listB,4) != p5) fail++;
 	if (listGetNthPerson(listB,5) != NULL) fail++;

  	/* remove the last person and check the results */

 	listC = listRemoveNthPerson(listB, listLength(listB) - 1);
	if (listC == NULL) fail++;
	if (listC->first != p5) fail++;
	if (listLength(listC) != 1) fail++;
	if (listLength(listB) != 4) fail++;
	if (listGetNthPerson(listB,0) != p3) fail++;
	if (listGetNthPerson(listB,1) != p2) fail++;
	if (listGetNthPerson(listB,2) != p1) fail++;
	if (listGetNthPerson(listB,3) != p6) fail++;
 	if (listGetNthPerson(listB,4) != NULL) fail++;

   	/* remove a middle person and check the results */

	listC = listRemoveNthPerson(listB,2);
	if (listC == NULL) fail++;
	if (listC->first != p1) fail++;
	if (listLength(listC) != 1) fail++;
	if (listLength(listB) != 3) fail++;
	if (listGetNthPerson(listB,0) != p3) fail++;
	if (listGetNthPerson(listB,1) != p2) fail++;
	if (listGetNthPerson(listB,2) != p6) fail++;
 	if (listGetNthPerson(listB,3) != NULL) fail++;

 	if (fail) {
		printf("Fails (%i)\n",fail);
	} else printf("OK (did not test removal of first person)\n");
	fail = 0;

	printf("Testing listIntersection... ");

	/* the intersection of a list with the empty list should be NULL */

	if (listIntersection(listB,NULL) != NULL) fail++;
	if (listIntersection(NULL,listB) != NULL) fail++;

	/* test that two disjoint lists of length 1 have an empty intersection */

	listC = listNew(p1,NULL);
	listD = listNew(p5,NULL);
	if (listIntersection(listC,listD) != NULL) fail++;

	/* test that two disjoint lists >1 have an empty intersection */

	listC->next = listD;
	if (listIntersection(listC,listB) != NULL) fail++;

	/* test for intersection between two lists */

	listB = listNew(p6,NULL);
	listB = listNew(p2,listB);
	listB = listNew(p3,listB);

	listC = listIntersection(listA,listB);
	if (!listContainsPerson(listC,p3)) fail++;
	if (!listContainsPerson(listC,p2)) fail++;
	if (!listContainsPerson(listC,p6)) fail++;

	/* test the case where both lists are the same but different order */

	listC = listCopy(listA);
	listC = listReverse(listC);
	listD = listIntersection(listC,listA);
	if (listLength(listD) != listLength(listA)) fail++;
	if (!listContainsPerson(listC,p1)) fail++;
	if (!listContainsPerson(listC,p2)) fail++;
	if (!listContainsPerson(listC,p3)) fail++;
	if (!listContainsPerson(listC,p4)) fail++;
	if (!listContainsPerson(listC,p5)) fail++;
	if (!listContainsPerson(listC,p6)) fail++;

  	if (fail) {
		printf("Fails (%i)\n",fail);
	} else printf("OK\n");

 	return 0;
 }
