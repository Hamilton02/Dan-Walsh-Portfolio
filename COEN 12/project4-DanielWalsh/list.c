/*
 * Author: Daniel Walsh
 * Language: C
 * Purpose: provide function for implementation of set.c, radix.c, and maze.c
 */



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

//list struct: O(1)
struct list{
	int count;
	struct node *head;
	int (*compare)();
};

typedef struct list LIST;

//node struct: O(1)
struct node{
	void *data;
	struct node *next;
	struct node *prev;
};

typedef struct node NODE;


//create list O(1)
LIST *createList(int (*compare)()){

	//create and allocate the list
	struct list  *lp;
	lp = malloc(sizeof(struct list));
	assert(lp != NULL);

	//set count and compare
	lp->count = 0;
	lp->compare = compare;

	//allocate and set head/dummy node
	lp->head = malloc(sizeof(struct node));
	assert(lp->head != NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;	

	return lp;
}

//destroys the whole list O(n)
void destroyList(struct list *lp){


	//make current and next nodes
	NODE *pDel, *pNext;
	
	//make current node the head
	assert(lp != NULL);
	pDel = lp->head;

	//while loop through all of the nodes
	do{

		//set next node
		pNext = pDel->next;

		//free current node
		assert(pDel != NULL);
		free(pDel);

		//move onto the next
		pDel = pNext;
	}while(pDel != lp->head);

	//free the whole list
	free(lp);
}

//return number of items O(1)
int numItems(LIST *lp){

	return lp->count;
}


//adds to front of the list O(1)
void addFirst(LIST *lp, void *item){

	//create new node and set pointers and data
	NODE *pNew = malloc(sizeof(NODE));
	pNew->data = item;
	pNew->next = lp->head->next;
	pNew->prev = lp->head;
	
	//set next node
	NODE *pNext = lp->head->next;

	//change existing node pointers to new and count
	pNext->prev = pNew;
	lp->head->next = pNew;
	lp->count++;

}

//adds to the end of the list O(1)
void addLast(LIST *lp, void *item){
	
	//create new and previous node
	NODE *pNew = malloc(sizeof(NODE));
	NODE *pPrev = lp->head->prev;

	//set existing pointer to new 
	pPrev->next = pNew;
	lp->head->prev = pNew;
	

	//sets pointers and data of new and increment count
	pNew->data = item;
	pNew->next = lp->head;
	pNew->prev = pPrev;
	lp->count++;
	
}

//removes first element O(1)
void *removeFirst(LIST *lp){

	//checks if empty
	if(lp->count > 0){

		//create and set nodes
		NODE *pDel, *pNext;
		pDel = lp->head->next;
		pNext = pDel->next;

		//sets nodes to remove pDel
		lp->head->next = pNext;
		pNext->prev = lp->head;

		//decrement count and return
		lp->count --;
		return pDel->data;
	
	}
	
	//returns null if empty
	return NULL;
}

//removes the last element O(1)
void *removeLast(LIST *lp){

	//checks if empty
	if(lp->count > 0){

		//create and set nodes
		NODE *pDel, *pPrev;
		pDel = lp->head->prev;
		pPrev = pDel->prev;

		//set nodes to remove pDel
		lp->head->prev = pPrev;
		pPrev->next = lp->head;

		//decrement count and return
		lp->count--;
		return pDel->data;
	}

	//returns null if empty
	return NULL;

}

//returns first node O(1)
void *getFirst(LIST *lp){
	return lp->head->next->data;
}

//gets last node O(1)
void *getLast(LIST *lp){


	return lp->head->prev->data;
}

//finds given item O(n)
void *findItem(LIST *lp, void *item){

	//initialize compare variable
	int cmp = 0;
	
	//allocate and set search node
	struct node *pCur = malloc(sizeof(NODE));
	pCur = lp->head->next;

	//loops through list till hits the node
	while(pCur != lp->head){

		//compares item and data
		cmp = (*lp->compare)(pCur->data, item);
	
		//returns the node if found, move on if not found
		if(cmp == 0){
			return pCur;
		}else{
			pCur = pCur->next;
		}
		
	}
	
	//returns null if not found
	return NULL;

}

//removes given item O(1)
void removeItem(LIST *lp, void *item){

	//uses find item to ger pointer to item
	struct node *pDel = findItem(lp, item);

	//create and set nodes
	NODE *next,*prev;
	next = pDel->next;
	prev = pDel->prev;

	//if item exists, nodes around it point past it then decrements
	if(pDel != NULL){
		next->prev = pDel->prev;
		prev->next = pDel->next;
		assert(pDel != NULL);
		lp->count--;
	}

}

//returns array of all elements in the list O(n)
void *getItems(LIST *lp){

	//create and allocate returning array	
	void **ret;
	ret = malloc(sizeof(void*) *lp->count);

	//create and set moving node
	NODE *pCur = lp->head->next;
	
	//loops through all nodes and adds it to the array
	int i;
	for(i = 0; i < lp->count && pCur != lp->head; i++){
		ret[i] = pCur->data;
		pCur = pCur->next;
	}

	assert(lp->head != NULL);	
	
	return ret;

}
