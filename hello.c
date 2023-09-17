#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
void main(){
	int fd;
	char* filename= "helloworld.txt";
	fd = open(filename,O_RDWR);
	char buf[50] = "Hello, World!\n\r";
	write(fd,&buf,strlen(buf));
	close(fd);
}
