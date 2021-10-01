/*
 * Author: Daniel Walsh
 *
 * Language: C
 *
 * Purpose: test file for application 2
 */

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "set.h"

//sets max students
#define MAX_STUDENTS 3000

//global variables to keep track of last added student
int lastID;
int lastAge;

//driver function for college.c O(n)
int main(){

	//creates void pointer for deletion later
	void *pDel;

	//create random seed for random number generator
	time_t t;
	srand((unsigned) time(&t));

	int i, age, iD;

	//creates set to put students in
	SET *students = createSet(MAX_STUDENTS);

	//interts 1000 students into the set
	for(i = 0; i < 1000; i++){
		iD = lastID + (rand() % 2 + 1);
		lastID = iD;
		age = rand() % 13 + 18;
		lastAge = age;
		insert(students, age, iD);
	}

	//gets last student added, prints it, then deleted it if succussful
	pDel = deleteStud(students, lastID);
	
	if(pDel){
		age = getAge(pDel);
		iD = getID(pDel);

		printf("Delete Successful - Age: %d, ID: %d \n", age, iD);
		free(pDel);
	}else{
		printf("Delete Unseccussful \n");
	}

	
	//gets two students to search and prints them if found, then deletes them
	void *studID = searchID(students, lastID);
	void *studID2 = searchID(students, lastID - 1);


	if(studID != NULL){
		age = getAge(studID);
		iD = getID(studID);

		printf("Search Success - Age: %d, ID: %d \n", age, iD);
	}else{
		printf("Search Unseccessful \n");
	}
	if(studID2 != NULL){
		age = getAge(studID2);
		iD = getID(studID2);

		printf("Search Success - Age: %d, ID: %d \n", age, iD);
	}else{
		printf("Unseccessful Search \n");
	}
	free(studID);
	free(studID2);

	//destroys the entire data set
	destroyDataSet(students);
}


