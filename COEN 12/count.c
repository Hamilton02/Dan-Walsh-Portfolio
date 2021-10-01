#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	
	// create file pointer	
	FILE *txt;

	//open file
	txt = fopen(argv[1], "r");

	// use to define max character length
	char ch[30];

	// word counter
	int words=0;


	// check if file opens
	if(txt == NULL){
		printf("Invalid file name");;
	}

	 
	else
	{
		// loop to find words
		while(fscanf(txt, "%s", ch) == 1){
			
			// add to counter
			words += 1;
		}

		// print total words
		printf("%d total words", words);
		
	}
	// close file
	fclose(txt);
}
