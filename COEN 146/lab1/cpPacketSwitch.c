#include <stdio.h>
#include <stdlib.h>
#define _USE_LIBM_MATH_H
#include <math.h>

int  factorial(int i){
	int num, ret = 1;
	for(num = i; num > 0; num--){
		ret *= num;
	}
	return ret;
}

int main(){

	int linkBandwidth = 200;
	int userBandwidth = 20;
	int nCSusers = 0;

	double tPSusers = 0.10;
	int nPSusers = 19;
	double pPSusersBusy = 0;
	double pPSusersNotBusy = 0;	

	nCSusers = linkBandwidth / userBandwidth;
	printf("6a. nCSusers: %d\n", nCSusers);

	double pPSusers = tPSusers;
	printf("7a. pPSusers: %f\n", pPSusers);

	pPSusersNotBusy = 1 - pPSusers;
	printf("7b. pPSusersNotBusy: %f\n", pPSusersNotBusy);

	double otherNotBusy = pow(pPSusersNotBusy, nPSusers-1);
	printf("7c. All others not busy: %f\n", otherNotBusy);

	double oneSpecific = pPSusers * otherNotBusy;
	printf("7d. One specific user busy: %f\n", oneSpecific);

	double exactOneSpecific = nPSusers * oneSpecific;
	printf("7e. Exactly One Specific User Busy: %f\n", exactOneSpecific);

	double pow1 = pow(pPSusers, 10);
	double pow2 = pow(pPSusersNotBusy, nPSusers-10);
	float tenUsers = pow1* pow2;
	printf("7f. 10 Users Busy: %e\n", tenUsers);

	double binomialDistTop = factorial(nPSusers);
	double binomialDistBottom = factorial(10);
	double binomialDistBottom2 = factorial(nPSusers - 10);
	double binomialDistTotal = binomialDistTop / (binomialDistBottom * binomialDistBottom2);

	double tenSpecific = binomialDistTotal * tenUsers;
	printf("7g. 10 Specific Users: %e\n", tenSpecific);

	binomialDistBottom = factorial(11);
	binomialDistBottom2 = factorial(nPSusers - 11);
	binomialDistTotal = binomialDistTop / (binomialDistBottom * binomialDistBottom2);

	pow1 = pow(pPSusers, 11);
	pow2 = pow(pPSusersNotBusy, nPSusers - 11);
	double moreThanTen = binomialDistTotal * pow1 * pow2; 
	printf("7h. More than 10 Users: %e\n", moreThanTen);

	exit(0);
}

