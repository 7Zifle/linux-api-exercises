#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_READ 50
int main(int argc, char *argv[])
{
	int fd = -1;
	switch (argc) {
	case 2:
		fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		break;
	case 3:
		if (strncmp(argv[1], "-a", 2) == 0) {
			fd = open(argv[2], O_WRONLY | O_APPEND | O_CREAT,
				  S_IRUSR | S_IWUSR);
		}
		break;
	}
	if (fd == -1) {
		perror("opening file");
		return -1;
	}

	char buf[MAX_READ + 1];
	int buf_size = read(STDIN_FILENO, buf, MAX_READ);
	if (buf_size == -1) {
		perror("Error reading from stdin");
		return 1;
	}
	write(STDOUT_FILENO, buf, buf_size);
	if (fd != -1) {
		write(fd, buf, buf_size);
	}

	close(fd);
	return 0;
}
