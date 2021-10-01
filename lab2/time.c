/*
 * Author: Danny Walsh
 * Date: 4/9/21
 * Title: copy files with functions
 * Purpose: use fread and fwrite to copy a file
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main( int argc, char *argv[]){

	//create clock and counting double
	clock_t start, end;
	double cpu_time_used;
	
	//start the clock
	start = clock();

	//create files and buffer
	FILE *fp_src, *fp_dst;
	char buf[100];

	//opens the files
	fp_src = fopen(argv[1], "r");
	fp_dst = fopen(argv[2], "w");

	//reads and writes the bytes
	int bytes_read = fread(buf, 1, sizeof(buf), fp_src);
	int bytes_written = fwrite(buf, 1, bytes_read, fp_dst);

	//closes the files
	fclose(fp_src);
	fclose(fp_dst);

	//ends the clock and calculates the time
	end = clock();
	cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;

	//print how long it took
	printf("Time: %f\n", cpu_time_used);

}
