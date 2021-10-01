/*
 * Author: Danny Walsh
 * Date: 4/9/21
 * Title: copy files with functions
 * Purpose: use fread and fwrite to copy a file
 */

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[]){

	//create the files and buffer
	FILE *fp_src, *fp_dst;
	char buf[100];

	//opens the files
	fp_src = fopen(argv[1], "r");
	fp_dst = fopen(argv[2], "w");

	//reads and writes the bytes
	int bytes_read = fread(buf, 1, sizeof(buf), fp_src);
	int bytes_written = fwrite(buf, 1, sizeof(buf), fp_dst);

	//closes the files
	fclose(fp_src);	
	fclose(fp_dst);

}
