/*
 * Author: Danny Walsh
 * Date: 4/9/21
 * Title: Copy files with system
 * Purpose: Copy files with the system call functions
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[]){

	//creates the buffer
	char buf[100];

	//opens the files
	int fd_src = open(argv[1], O_RDONLY);
	int fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);

	//reads and writes the files
	int bytes_read = read(fd_src, buf, sizeof(buf));
	int bytes_written = write(fd_dst, buf, bytes_read);

	//closes the files
	close(fd_src);
	close(fd_dst);

}
