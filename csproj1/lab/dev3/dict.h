#ifndef DICT_H
#define DICT_H

typedef struct _node {
	char*	key;
	int	count;
	struct _node* next;
} Node;

typedef struct _dictionary {
	int	n;		/* size of dictionary table t[] */
	Node	**t;           /* t[i] == a node or NULL	*/
} Dictionary;

Dictionary *dictionaryNew(int n);

int dictionaryUpdate(Dictionary *d, char* text);

void dictionaryDump(Dictionary *d);

#endif
