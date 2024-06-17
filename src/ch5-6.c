#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *file = "testfile-ch5-6";
	int fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	int fd2 = dup(fd1);
	int fd3 = open(file, O_RDWR);
	write(fd1, "Hello,", 6);
	write(fd2, " world", 6);
	lseek(fd2, 0, SEEK_SET);
	write(fd1, "HELLO,", 6);
	write(fd3, "Gidday", 6);

	close(fd1);
	close(fd2);
	close(fd3);
	return EXIT_SUCCESS;
}

