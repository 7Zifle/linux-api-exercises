#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd = open("testfile", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}
	int dfd = dup(fd);
	if (dfd == -1) {
		perror("dup");
		return EXIT_FAILURE;;
	}
	int fd_status = fcntl(fd, F_GETFL);
	int dfd_status = fcntl(dfd, F_GETFL);
	if (fd_status != dfd_status) {
		fprintf(stderr, "FDs have different statuses\n");
	}
	int fd_offset = lseek(fd, 0, SEEK_CUR);
	int dfd_offset = lseek(dfd, 0, SEEK_CUR);
	if (fd_offset != dfd_offset) {
		fprintf(stderr, "FDs have different offsets\n");
	}
	return EXIT_SUCCESS;
}
