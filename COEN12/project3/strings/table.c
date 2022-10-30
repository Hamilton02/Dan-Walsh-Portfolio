/*
 *Daniel Walsh
 *Language: C
 *Function: Provide function implementation for parity and unique strings
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"


//create struct set
typedef struct set{
	int count;
	int length;

	// strings
	char **data;
	//hash spot status
	char *flags;
}SET;



//hash function O(1)
static unsigned strhash(SET *sp, char *s){
	unsigned hash = 0;

	while(*s != '\0'){
		hash = 31 * hash + *s ++;
	}

	// mod it by  length to make it modulo hash
	return (hash) % sp->length;
}

//creates the set O(n)
SET *createSet(int maxElts){

	//create and allocate SET
	SET *sp;
	sp = malloc (sizeof (SET));
	assert(sp != NULL);

	//set int values
	sp->count=0;
	sp->length = maxElts;

	//malloc and set every flag to E
	sp->flags = malloc(sizeof(char)*maxElts);
	int i;
	for(i = 0; i < sp->length; i++){
		sp->flags[i] = 'E';
	}

	//malloc strings
	sp->data = malloc( sizeof(char*) *maxElts);
	assert(sp->data!=NULL);

	return sp;

}

//destroys the entire set O(n)
void destroySet(SET *sp){

	//avoids double free
	assert(sp != NULL);
	
	//loop through to remove all elements
	int i;
	for(i = 0; i < sp->count; i++){		
		free(sp->data[i]);
	}
	
	//frees the array
	free(sp->data);

	//frees the SET
	free(sp);
}


//returns number of elements O(1)
int numElements(SET *sp){
	return sp->count;
}

// adds element to set O(n)
void addElement(SET *sp, char *elt){

	// makes sure element isn't in SET
	char *a = findElement(sp, elt);

	//gets hash for elt
	int hashNum = strhash(sp, elt);

	//checks if in SET already
	if(a == NULL){

		// loops to find next open spot
		while(sp->flags[hashNum] == 'F'){
			hashNum++;
		}

		//sets everything in first open hash spot
		sp->data[hashNum] = strdup(elt);
		sp->flags[hashNum] = 'F';
		sp->count++;
	}

}


//returns all filled elements O(n)
char ** getElements(SET *sp){

	char **elts;

	int i, j;

	assert(sp!= NULL);

	//allocate new memory to return new pointer
	elts = malloc(sizeof(char*) * sp->count);
	assert(elts != NULL);

	//looks for all filled elements and adds them to new pointer
	for(i = 0, j = 0; i < sp->length; i++){
		if(sp->flags[i] == 'F'){
			elts[j++] = sp->data[i];
		}
	}

	return elts;
}

//finds given element O(n)
char *findElement(SET *sp, char *elt){

	//finds hash spot
	int hashNum = strhash(sp, elt);

	//ensures not accessing NULL data
	if(sp->data[hashNum] != NULL){
		
		//loop to searchstring of filled and deletes elements
		do{

			//checks if filled and if it matches
			if(sp->flags[hashNum] == 'F'){
				if(strcmp(sp->data[hashNum], elt) == 0){
					return sp->data[hashNum];

				// keep searching cluster if not a match
				}else{
					hashNum++;
				}

			// keeps going incase of D
			}else{
				hashNum++;
			}
		}while(sp->flags[hashNum] == 'F' || sp->flags[hashNum] == 'D');
	}

	//returns NULL if not found
	return NULL;
}

//removes elt if found O(n)
void removeElement(SET *sp, char *elt){

	//gets hash spot
	int hashNum = strhash(sp, elt);

	//checks to make sure not accessing NULL data
	if(sp->data[hashNum] != NULL){

		//loop through cluster of filled and deleted spots
		while(sp->flags[hashNum] == 'F' || sp->flags[hashNum] == 'D'){

			//keeps going past deleted
			if(sp->flags[hashNum] == 'D'){
				hashNum++;

			//keeps going if not found
			}else if(strcmp(sp->data[hashNum], elt) != 0){
				hashNum++;

			//deletes if found
			}else{
				sp->flags[hashNum] = 'D';
				assert(sp->data[hashNum] != NULL);
				free(sp->data[hashNum]);
				sp->count--;
				break;
			}
		}
	}
	
}
