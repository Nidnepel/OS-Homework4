#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

const int BUFFER_SIZE = 32;

int main(int argc, char **argv) {
	int fd;
	char buffer[BUFFER_SIZE + 1];
	ssize_t read_bytes;

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		printf("Can not open file\n");
		exit(-1);
	}
	int fd2;
	if ((fd2 = open(argv[2], O_WRONLY | O_CREAT, 0666)) < 0) {
		printf("Can not open file\n");
		exit(-1);
	}
	do {
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1) {
			printf("Can not read this file\n");
			exit(-1);
		}
		buffer[read_bytes] = '\0';
		int size2 = write(fd2, buffer, BUFFER_SIZE);
		if (size2 != BUFFER_SIZE) {
			printf("Can not write all strings");
			exit(-1);
		}
	} while (read_bytes == BUFFER_SIZE);
	
	if (close(fd) < 0) {
		printf("Can not close file\n");
	}

	if (close(fd2) < 0) { 
		printf("Can not close file\n");
	}
	return 0;
}
