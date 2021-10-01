/*
 * Author: Daniel Walsh
 *
 * Language: C
 *
 * Purpose: Test file for application 1
 */



#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "set.h"
#define MAX_STUDENTS 3000

//global variables to keep track of last age and iD to print that student
int lastID;
int lastAge;

//driver function for college.c O(n)
int main(){

	//create void pointer for deletion later
	void *pDel;

	//create random number generator random seed
	time_t t;
	srand((unsigned) time(&t));

	int i, age, iD;

	//create set to put students into
	SET *students = createDataSet(MAX_STUDENTS);

	//put 1000 students into set
	for(i = 0; i < 1000; i++){
		iD = lastID + (rand() % 2 + 1);
		lastID = iD;
		age = rand() % 13 + 18;
		lastAge = age;
		insertStud(students, age, iD);
	}

	//gets the max age gap and prints it
	int ageGap = maxAgeGap(students);
	printf("max age gap: %d \n", ageGap);

	//deletes the last student added and printds if found
	pDel = deleteStud(students, lastAge, lastID);
	
	if(pDel){
		age = getAge(pDel);
		iD = getID(pDel);

		printf("Delete Successful - Age: %d, ID: %d \n", age, iD);
		free(pDel);
	}else{
		printf("Delete Unseccussful \n");
	}

	//gets the size and array of age group and prints all of them before freeing them
	int groupLen = getListCount(students, 18);
	void **ageGroup = searchAge(students, 18);

	//print every student in age group
	for(i = 0; i < groupLen; i++){
		age = getAge(ageGroup[i]);
		iD = getID(ageGroup[i]);

		printf("Age: %d, iD: %d\n", age, iD);

		free(ageGroup[i]);
	}

	//free array of students
	free(ageGroup);

	//destroys entire data set
	destroyDataSet(students);
}


