/*
 * Daniel Walsh
 * Language: C
 * Purpose: Create functions to implement for parity and unique genral
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"


//creates struct variables O(1)
typedef struct set{

	//counter variable
	int count;
	int length;

	//strings
	char **data;

	//hash spot status
	char *flags;

	//passed functions
	int (*compare)();
	unsigned (*hash)();
}SET;

//gets hash num from created program and mods by length O(1)
static int search(SET *sp, void *elt){

	//gets hash num from passed function and mods by lengths to make it modulo hash
	int  hash = (*sp->hash)(elt) % sp->length;	
	
	return hash;	

}


//creates SET O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	
	//creates and allocates the set
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	
	//sets int values
	sp->count = 0;
	sp->length = maxElts;

	//allocates flags and sets all to E
	sp->flags = malloc(sizeof(char) *maxElts);
	int i;
	for(i = 0; i < sp->length; i++){
		sp->flags[i] = 'E';
	}

	//allocates memory for strings
	sp->data = malloc(sizeof(char*) *maxElts);

	//sets passed functions
	sp->compare = compare;

	sp->hash = hash;

	return sp;

}

//destroys the entire set O(1)
void destroySet(SET *sp){

	//checks and deletes data
	assert(sp->data != NULL);
	free(sp->data);

	//checks and deletes the SET
	assert(sp->data != NULL);
	free(sp);

}

//returns number of elements O(1)
int numElements(SET *sp){
	return sp->count;
}


//adds element to set if not already in it O(n)
void addElement(SET *sp, void *elt){

	//creates pointer for check
	char *a = findElement(sp, elt);

	//gets hash spot for search
	int hashNum = search(sp, elt);

	//checks if in SET
	if(a == NULL){

		//loops through looking for next open element
		while(sp->flags[hashNum] == 'F'){
			hashNum++;
		}

		//sets elt in open hash spot	
		sp->data[hashNum] = strdup(elt);
		sp->flags[hashNum] = 'F';
		sp->count++;

	}	

}

//finds given element O(n)
void *findElement(SET *sp, void *elt){

	int cmp;

	//gets hash spot
	int hashNum = search(sp, elt);

	//makes sure not accessing NULL data
	if(sp->data[hashNum] != NULL){
	
		// loop through cluster of filled and deleted elements
		do{

			//checks filled elements
			if(sp->flags[hashNum] == 'F'){

				//compares and returns if found
				int cmp = (*sp->compare)(elt, sp->data[hashNum]);
				if(cmp == 0){
					return sp->data[hashNum];
				//passes by elements if not a match
				}else{
					hashNum++;
				}

			//passes by deleted elements
			}else{
				hashNum++;
			}
		}while(sp->flags[hashNum] == 'F' || sp->flags[hashNum] == 'D');
	}

	//returns NULL if not found
	return NULL;
		
}

//removes given element O(n)
void removeElement(SET *sp, void *elt){

	//gets hash spot
	int hashNum = search(sp, elt);

	//makes sure not accessing NULL data
	if(sp->data[hashNum] != NULL){

		//loops through cluster of filled and deleted cluster that do not match
		while((*sp->compare)(elt, sp->data[hashNum]) != 0 && sp->flags[hashNum] == 'F'|| sp->flags[hashNum] == 'D'){
			hashNum++;
		}

		//if found, it states everything as deleted while other function deltes the data
		sp->flags[hashNum] = 'D';
		assert(sp->data[hashNum] != NULL);
		sp->count--;
	}

}

//returns the filled elements O(n)
void *getElements(SET *sp){

	//creates new set
	void **elts;
	elts = malloc(sizeof(void*) *sp->count);
	int i, j;

	//finds all filled elements and adds them to elts
	for(i = 0, j = 0; i < sp->length; i++){
		if(sp->flags[i] == 'F'){
			elts[j++] = sp->data[i];
		}
	}

	return elts;

}


