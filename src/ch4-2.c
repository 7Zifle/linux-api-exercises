#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "USAGE ch4-2 src dest\n");
		return 1;
	}
	int src_fd = open(argv[1], O_RDONLY);
	if (src_fd == -1) {
		perror("open src");
		return 1;
	}
	int dest_fd =
		open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (dest_fd == -1) {
		perror("open dest");
		return 1;
	}
	while (1) {
		char buf[50];
		int read_size = read(src_fd, buf, 50);
		if (read_size == 0) {
			break;
		}
		if (read_size == -1) {
			perror("reading src");
			return 1;
		}
		write(dest_fd, buf, read_size);
	}
	return 0;
}
