#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int ldup(int fd)
{
	return fcntl(fd, F_DUPFD, 0);
}

int ldup2(int oldfd, int newfd)
{
	int fd = fcntl(oldfd, F_DUP2FD, newfd);
	return fd;
}

int main(int argc, char *argv[])
{
	int fd = open("testfile", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}
	int newfd = ldup(fd);
	if (newfd == -1) {
		perror("ldup fd");
		return EXIT_FAILURE;
	}
	int newnewfd = ldup2(fd, 3);
	if (newnewfd == -1) {
		perror("ldup2 fd, 3");
		return EXIT_FAILURE;
	}
	close(newfd);
	close(newnewfd);
	return EXIT_SUCCESS;
}
