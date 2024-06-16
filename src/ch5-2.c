#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "USAGE ch5-2 file");
		return 1;
	}
	int fd = open(argv[1], O_APPEND | O_WRONLY);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	int seeked = lseek(fd, 0, SEEK_SET);
	if (seeked == -1) {
		perror("lseek");
		return 1;
	}
	char buffer[] = "hello";
	int wrote = write(fd, buffer, 5);
	if (wrote == -1) {
		perror("write");
		return 1;
	}
	return EXIT_SUCCESS;
}
