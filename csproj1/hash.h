#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

typedef struct _Node{
	char *key;
	void *value;
	struct _Node* next;
}Node;

typedef struct _hashRoot{
	int count;
	int size;
	Node **array;
}HashRoot;


HashRoot *hashCreate(int initBuckets);

void hashFree(HashRoot *ht,void(*f)(char *key, void *value));

void *hashSearch(HashRoot *ht,char *key );

int hashInsert(HashRoot *ht, char *key, void*);

int hashApply(HashRoot *ht,void(*ElemTarray)(char *key,void *value));

int hash(char *key, int size);

void printOut(HashRoot *ht);

#endif
