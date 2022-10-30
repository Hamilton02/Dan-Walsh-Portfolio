/*
 *Author: Daniel Walsh
 *
 * Language: C
 *
 * Purpose: provide implementation for college.c for application 2
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "set.h"

//define set struct
typedef struct set SET;
struct set{

	int length;
	int count;
	
	void **data;
	char *flags;
};

//define student struct
typedef struct stud STUD;
struct stud{

	int age;
	int iD;

};

//return hash number modding by 3001 because it is the closest prime number to 3000 O(1)
static int hashNum(int i){

	int hash = i % 3001;

}

//creates a set O(n)
SET *createSet(int maxStud){

	//create and allocate the set
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);

	//set the ints
	sp->count = 0;
	sp->length = maxStud;

	//create and set all the flags to empty
	sp->flags = malloc(sizeof(char) * maxStud);
	int i;
	for(i = 0; i < sp->length; i++){
		sp->flags[i] = 'E';
	}

	//allocates the data array 
	sp->data = malloc(sizeof(char) * maxStud);

	return sp;
}

//destroys the data set
void destroyDataSet(SET *sp){

	//assert not null and frees the set
	assert(sp != NULL);
	free(sp);
}


//takes in unique iD and returns the student with it O(n)
void *searchID(SET *sp, int iD){

	//gets hash number
	int hash = hashNum(iD);

	//create student node to be moved until found		
	STUD *cur = NULL;

	//ensures first element isn't empt
	if(sp->data[hash] != NULL){

		//loops through cluster of filled and deleted student 
		do{
			//moves the node one over
			cur = sp->data[hash];

			//checks if current element is filled, in not moves on
			if(sp->flags[hash] == 'F'){	

				//if filled, returns it and changes variables to delete it, if not, moves on
				if(iD = cur->iD){
					sp->count--;
					sp->flags[hash] = 'D';
					return cur;
				}else{
					hash++;
				}
			}else{
				hash++;
			}
		}while(sp->flags[hash] == 'F' || sp->flags[hash] == 'D');
	}
	return NULL;
}

//inserts student into set O(n)
void insert(SET *sp, int age, int iD){

	//allocate new student
	STUD *new = malloc(sizeof(STUD));

	//sets the student's ints
	new->iD = iD;
	new->age = age;

	//gets hash number 
	int hash = hashNum(iD);

	//loops through cluster to find it a place
	while(sp->count < sp->length && sp->flags[hash] == 'F'){
		hash++;
	}

	//sets spot to new node and changes variables
	sp->data[hash] = new;
	sp->count++;
	sp->flags[hash] = 'F';

}

//deletes given student O(n)
void *deleteStud(SET *sp, int iD){

	//gets hash number
	int hash = hashNum(iD);

	//create moving node and move through cluster to find student's iD
	STUD *cur;
	while(sp->flags[hash] != 'E'){
		cur = sp->data[hash];

		//if found, it returns it and deletes from det, if not, moves on
		if(cur->iD == iD){
			sp->count--;
			sp->flags[hash] = 'D';
			return cur;
		}else{
			hash++;
		}
	}
	return NULL;
}


//returns iD for printing purposes O(1)
int getID(STUD *stud){
	return stud->iD;
}

//returns age for printing purposes O(1)
int getAge(STUD *stud){
	return stud->age;
}
