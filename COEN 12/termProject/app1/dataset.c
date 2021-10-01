/*
 *Author: Daniel Walsh
 *
 *Language: C
 *
 * Purpose: Implement college.c for application 1
 */



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"

//sets 13 possible lists because there are 13 possible ages
# define HASH 13

//define set struct
typedef struct set SET;
struct set{
	int length;
	int count;

	LIST **ages;
};

//define student stuct
typedef struct stud STUD;
struct stud{

	int age;
	int iD;

	STUD *next;
	STUD *prev;
};

//define list struct
typedef struct list LIST;
struct list{

	int count;
	STUD *head;
	
};

//function to return the hash O(1)
int hashNum(int i){
	
	int hash = (i - 18) % HASH;
	return hash;
}

//return length of a list for the search in college.c O(1)
int getListCount(SET *sp, int age){
	LIST *ret = sp->ages[hashNum(age)];
	return ret->count;
} 

//creates a list to be put into the set O(1)
static LIST *createList(){

	//create and allocate the list
	LIST *lp;
	lp = malloc(sizeof(LIST));
	assert(lp != NULL);

	//set the count
	lp->count = 0;

	//allocate and set the dummy node
	lp->head = malloc(sizeof(STUD));

	lp->head->next = lp->head;
	lp->head->prev = lp->head;

	return lp;	

}

//creates the data set O(hash)
SET *createDataSet(int maxStud){

	//allocate the set
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);

	//set the ints
	sp->count = 0;
	sp->length = HASH;

	//allocte the list array
	sp->ages = malloc(sizeof(LIST*) *sp->length);
	assert(sp->ages != NULL);

	//create all the lists
	int i;
	for(i = 0; i < sp->length; i++){
		sp->ages[i] = createList();
	}

	return sp;	
}

//destroys the data set O(n)
void destroyDataSet(SET *sp){

	//create moving variables
	STUD *pDel, *pNext;
	LIST *cur;

	//deletes all elements in each list
	int i;
	for(i = 0; i < sp->length; i++){
		cur = sp->ages[i];
		assert(cur != NULL);

		pDel = cur->head;

		do{
			pNext = pDel->next;
			
			assert(pDel != NULL);
			free(pDel);

			pDel = pNext;

		}while(pDel != cur->head);
	
		free(cur);
	}

	//free the list array
	assert(sp->ages != NULL);
	free(sp->ages);

	//free the set
	assert(sp != NULL);
	free(sp);
}

//returns all studetns of a specified age O(n)
void **searchAge(SET *sp, int age){
	
	//get hash number
	int hash = hashNum(age);

	//create moving variables and alloacate the returning array
	STUD *pCur, *pTemp;
	LIST *ageList = sp->ages[hash];	
	void **ret = malloc(sizeof(void*) *ageList->count);

	//set the current list to loop through
	pCur = ageList->head->next;

	//loops through the entire list and adds all students to the array
	int i;
	for(i = 0; i < ageList->count && pCur != ageList->head; i++){
		ret[i] = pCur;
		pTemp = pCur;
		pCur = pCur->next;
		ageList->head->next = pCur;
		
	}

	return ret;
}

//inserts a student to the end of a list O(1)
void insertStud(SET *sp, int age, int iD){

	//get hash number
	int hash = hashNum(age);

	//define list with student's age
	LIST *cur = sp->ages[hash];

	//create new and previous nodes
	STUD *pNew = malloc(sizeof(STUD));
	STUD *pPrev = cur->head->prev;

	//set existing nodes to pNew
	pPrev->next = pNew;
	cur->head->prev = pNew;

	//first node case
	if(cur->head->next == cur->head){
		cur->head->next = pNew;
	}

	//set all variables and pointers of new node
	pNew->age = age;
	pNew->iD = iD;
	pNew->next = cur->head;
	pNew->prev = pPrev;
	cur->count++;
	sp->count++;
}

//deletes given student O(n)
void *deleteStud(SET *sp, int age, int iD){

	//get hash number
	int hash = hashNum(age);

	//set moving nodes and list 
	LIST *cur = sp->ages[hash];
	STUD *next, *prev;
	STUD *pCur = cur->head->next;

	//loop through the list and breaks if the iD's match
	while(pCur != cur->head){
		if(pCur->iD == iD){
			break;
		}else{
			pCur = pCur->next;
		}
	}

	//sets all pointers around found student and modifies counts if found
	if(pCur != cur->head){
		next = pCur->next;
		prev = pCur->prev;

		next->prev = pCur->prev;
		prev->next = pCur->next;
		assert(pCur != NULL);
		cur->count--;
		sp->count--;
	}else{
		pCur = NULL;
	}

	//returns the student
	return pCur;
}

//returns the maximum age gap O(n)
int maxAgeGap(SET *sp){

	//create lists for oldest found and youngest found
	LIST *young = NULL, *old = NULL;

	//create integers
	int i = 0;
	int youngAge, oldAge;
	
	//loops through starting at the bottom to find youngest group
	while(young == NULL){
		LIST *cur = sp->ages[i];
		if(cur->head->prev == cur->head){
			i++;
		}else{
			young = cur;
			youngAge = i;
		}
	}

	//loops through starting at the top to find the oldest group
	int j = sp->length-1;
	while(old == NULL){
		LIST *cur = sp->ages[j];
		if(cur->head->prev == cur->head){
			j--;
		}else{
			old = cur;
			oldAge = j;
		}
	}
	printf("old: %d, young: %d \n", oldAge, youngAge);

	//returns the difference between oldest and youngest
	return oldAge - youngAge;
}

//returns a student age for printing purposes O(1)
int getAge(STUD *stud){
	return stud->age;
}

//returns a student iD for printint purposes O(1)
int getID(STUD *stud){
	return stud->iD;
}
