/*
 * Name: Daniel Walsh
 * Date: 4/7/21
 * Title: Lab1 - Packet switching
 */

#include <stdio.h>
#include <stdlib.h>

//pow function
#define _USE_LIBM_MATH_H
#include <math.h>

//for binomial distribution in 
int  factorial(int i){

	//take the input, and multiply by every whole number below it
	int num, ret = 1;
	for(num = i; num > 0; num--){
		ret *= num;
	}
	return ret;
}

//main driver function
int main(){

	//bandwidth variables
	int linkBandwidth = 200;
	int userBandwidth = 20;
	int nCSusers = 0;

	//probability variables
	double tPSusers = 0.10;
	int nPSusers = 19;
	double pPSusersBusy = 0;
	double pPSusersNotBusy = 0;	

	//6a bandwidth divided by user bandwidth
	nCSusers = linkBandwidth / userBandwidth;
	printf("6a. nCSusers: %d\n", nCSusers);

	//7a defines perecntage user is active
	double pPSusers = tPSusers;
	printf("7a. pPSusers: %f\n", pPSusers);

	//7b percentage users arent active
	pPSusersNotBusy = 1 - pPSusers;
	printf("7b. pPSusersNotBusy: %f\n", pPSusersNotBusy);

	//7c percent chance all other users aren't busy
	double otherNotBusy = pow(pPSusersNotBusy, nPSusers-1);
	printf("7c. All others not busy: %f\n", otherNotBusy);

	//7d one specfic user is transmitting and all others aren't
	double oneSpecific = pPSusers * otherNotBusy;
	printf("7d. One specific user busy: %f\n", oneSpecific);

	//7e probability any specific user is transmitting and others are not
	double exactOneSpecific = nPSusers * oneSpecific;
	printf("7e. Exactly One Specific User Busy: %f\n", exactOneSpecific);

	//7f. proability 10 users are transmitting
	double pow1 = pow(pPSusers, 10);
	double pow2 = pow(pPSusersNotBusy, nPSusers-10);
	float tenUsers = pow1* pow2;
	printf("7f. 10 Users Busy: %e\n", tenUsers);

	//binomial distribution calculation
	double binomialDistTop = factorial(nPSusers);
	double binomialDistBottom = factorial(10);
	double binomialDistBottom2 = factorial(nPSusers - 10);
	double binomialDistTotal = binomialDistTop / (binomialDistBottom * binomialDistBottom2);

	//7g. probability 10 specific users are transmitting at the same time
	double tenSpecific = binomialDistTotal * tenUsers;
	printf("7g. 10 Specific Users: %e\n", tenSpecific);

	//binomial distribution for more than 10 users
	binomialDistBottom = factorial(11);
	binomialDistBottom2 = factorial(nPSusers - 11);
	binomialDistTotal = binomialDistTop / (binomialDistBottom * binomialDistBottom2);

	//7h. probability more than 10 specific users are transmitting
	pow1 = pow(pPSusers, 11);
	pow2 = pow(pPSusersNotBusy, nPSusers - 11);
	double moreThanTen = binomialDistTotal * pow1 * pow2; 
	printf("7h. More than 10 Users: %e\n", moreThanTen);

	exit(0);
}

