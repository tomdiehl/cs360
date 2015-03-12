#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>
#include <math.h>


#define CRC64_REV_POLY      0x95AC9329AC4BC9B5ULL
#define CRC64_INITIALIZER   0xFFFFFFFFFFFFFFFFULL
#define CRC64_TABLE_SIZE    256


/*****************************
Hash Function
*****************************/
unsigned long long crc64(char* string) {
    static int initFlag = 0;
    static unsigned long long table[CRC64_TABLE_SIZE];
    
    if (!initFlag) { initFlag++;
        for (int i = 0; i < CRC64_TABLE_SIZE; i++) {
            unsigned long long part = i;
            for (int j = 0; j < 8; j++) {
                if (part & 1)
                    part = (part >> 1) ^ CRC64_REV_POLY;
                else part >>= 1;
            }
            table[i] = part;
        }
    }
    
    unsigned long long crc = CRC64_INITIALIZER;
    while (*string)
        crc = table[(crc ^ *string++) & 0xff] ^ (crc >> 8);
    return abs(crc);
}
/*********************************
Create Function
*********************************/

HashRoot *hashCreate(int initBuckets){
    HashRoot *newHash;  
    if(initBuckets < 1) return NULL;

    newHash = malloc(sizeof(HashRoot));
    newHash->array = malloc(sizeof(Node*)*initBuckets);

    for(int i = 0; i < initBuckets; i++){
      newHash->array[i]= NULL;
    } 
    newHash->size = initBuckets;
    newHash->count = 0; 
    return newHash;
}
/*************************************
Search Function
****************************************/
void *hashSearch(HashRoot *ht,char *key ){
    int index = hash(key,ht->size);
    Node *CurrNode = ht->array[index];

    while(CurrNode != NULL){;
      if(strcmp(CurrNode->key,key) == 0){
      	return CurrNode->value;
      }
      else{
	CurrNode = CurrNode->next;
      }
    }
    return NULL;
}

/*******************************************
Hash keys
*********************************************/
int hash(char *key, int size){
    return ((int)crc64(key) % size);
}

/*********************************************
Grow Function
**********************************************/
void hashGrow(HashRoot *ht){
    int newsize = (((ht->size)/2)+1);
    HashRoot *temp = hashCreate(newsize*6);
    for(int index = 0 ; index < ht->size ;index++) {
        Node *CurrNode = ht->array[index];
        while(CurrNode != NULL){
            hashInsert(temp,CurrNode->key,CurrNode->value);
	    free(CurrNode);
            CurrNode = CurrNode->next;    
	}
    }
     free(ht->array);
    
     ht->size = temp->size;
     ht->count =temp->count;
     ht->array = temp->array;
     
     free(temp);
}
/***********************************************
Insert Fucntion
*************************************************/
int hashInsert(HashRoot *ht, char *key, void *value){
    if(((ht->count)/(ht->size)) >= 4) hashGrow(ht);        //Check if hash table needs to grow
    if(hashSearch(ht,key) == NULL){                        //if elem not already in table add it
        int index = hash(key,ht->size);
        Node *new = (Node *)malloc(sizeof(Node));
        new->key = key;
        new->value = value;
        new->next = ht->array[index];
        ht->array[index] = new;
        ht->count++;
        return 1;                                           //return 1 for successful add
    }
    else return 0;                                         //if elem in table already return 0;
}

/***********************************************
Print Fucntion
*************************************************/
void printOut(HashRoot *ht){
    for(int index = 0 ; index < ht->size ;index++) {
        Node *CurrNode = ht->array[index];
        while(CurrNode != NULL){
            printf("index = %i, key = %s, value = %i \n",index, CurrNode->key, *((int *)CurrNode->value));
            CurrNode = CurrNode->next; 
        }
     }   
}

/***********************************************
APPLY Fucntion
*************************************************/
int hashApply(HashRoot *ht,void (*f)(char *key,void *value)){
    int apTo = 0;
    for(int index = 0 ; index < ht->size ;index++) {
        Node *CurrNode = ht->array[index];
        while(CurrNode != NULL){
    		f(CurrNode->key, CurrNode->value);       
		CurrNode = CurrNode->next;
		apTo++; 
        }
    }   
    return apTo;
}

/***********************************************
Free Fucntion
*************************************************/
void hashFree(HashRoot *ht,void(*f)(char *key, void *value)){
  
    for(int index = 0 ; index < ht->size ;index++) {
        Node *CurrNode = ht->array[index];
	while(CurrNode != NULL){
	    f(CurrNode->key, CurrNode->value);       
	    free(CurrNode);
	    CurrNode = CurrNode->next; 
	}
    }   
    free(ht->array);
    free(ht);	
}












