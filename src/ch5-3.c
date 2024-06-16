#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr, "USAGE: ch5-3 filename num-bytes [x]");
		return EXIT_FAILURE;
	}
	int fd;
	if (argc == 4) {
		fd = open(argv[1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	} else {
		fd = open(argv[1], O_CREAT | O_WRONLY | O_APPEND,
			S_IRUSR | S_IWUSR);
	}
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}
	int num = atol(argv[2]);
	char buf[] = { '0' };
	if (argc == 4) {
		for (int i = 0; i < num; i++) {
			lseek(fd, 0, SEEK_END);
			write(fd, buf, 1);
		}
	} else {
		for (int i = 0; i < num; i++) {
			write(fd, buf, 1);
		}
	}

	return EXIT_SUCCESS;
}
