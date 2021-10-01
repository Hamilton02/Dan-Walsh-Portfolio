/*
 * Author: Daniel Walsh
 * Language: C
 * Purpose: implement list.c using a hash table for unique.c and parity.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "list.h"

const int alpha = 20;

//set struct O(1)
typedef struct set{

	int count;
	int length;

	void **lists;

	int (*compare)();
	unsigned(*hash)();

}SET;

//creates set O(n)
SET *createSet(int maxEtls, int (*compare)(), unsigned (*hash)()){
	
	//create and allocate the set
	int i;
	SET *sp;
	assert(compare != NULL && hash != NULL);
	sp = malloc(sizeof(SET));

	//sets int values
	assert(sp != NULL);
	sp->count = 0;
	//this keeps the load factor at 20
	sp->length = maxEtls / alpha;

	//initializes the passed functions
	sp->compare = compare;
	sp->hash = hash;

	//creates and allocates array of lists
	sp->lists = malloc(sizeof(void*) *sp->length);
	assert(sp->lists != NULL);

	//creates list for every hash spot
	for(i = 0; i < sp->length; i++){
		sp->lists[i] = createList(sp->compare);
	}


	return sp;
}

//destroys entire set O(n)
void destroySet(SET *sp){

	//loops through every hash and destroys the list
	int i;
	for(i = 0; i < sp->length; i++){
		assert(sp->lists[i] != NULL);
		destroyList(sp->lists[i]);
	}

	//frees the lists array
	assert(sp->lists != NULL);
	free(sp->lists);

	//frees the set
	assert(sp != NULL);
	free(sp);
}

//returns number of elements O(1)
int numElements(SET *sp){
	return sp->count;
}

//adds element O(1)
void addElement(SET *sp, void *elt){

	//gets hash num and mods by length
	int hash = (*sp->hash)(elt) % sp->length;
	
	//adds to last and increments
	addLast(sp->lists[hash], elt);
	sp->count++;
	
}

//removes given element O(1)
void removeElement(SET *sp, void *elt){

	//gets hash number and mods by length
	int hash = (*sp->hash)(elt) % sp->length;

	//removes given element and decrements
	removeItem(sp->lists[hash], elt);
	sp->count--;

}

//finds element O(1) (O((a+1)/2) expected)
void *findElement(SET *sp, void *elt){

	//gets hash number and mods by length
	int hash = (*sp->hash)(elt) % sp->length;

	//returns result of findItem
	return findItem(sp->lists[hash], elt);
}

//returns array of all elements 
void *getElements(SET *sp){

	//create and alloacate arrays
	void **elt, **temp;	
	elt  = malloc(sizeof(void*) *sp->count);
	temp = malloc(sizeof(void*) *sp->length);


	int i, j;
	int count = 0;

	//loops through all hash spots
	for(i = 0; i < sp->length; i++){
			//sets temporary array to the one in the current spot
			temp = getItems(sp->lists[i]);

		//loops through temporary array and puts them all in the returned array
		for(j = 0; j < numItems(sp->lists[i]); j++){
			if(temp[j] != NULL){
				elt[count] = temp[j];
				count++;
			}
		}
			
	}

	//returns final array
	return elt;
}
