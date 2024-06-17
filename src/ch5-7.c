#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/_iovec.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/uio.h>
#include <malloc.h>

int lreadv(int fd, struct iovec *iov, int iovcnt) {
	for (int i = 0; i < iovcnt; i++) {
		if(read(fd, iov[i].iov_base, iov[i].iov_len) == -1) {
			perror("read");
			return EXIT_FAILURE;
		}
	}
	return 0;
}

int lwritev(int fd, struct iovec *iov, int iovcnt) {
	for (int i = 0; i < iovcnt; i++) {
		if (write(fd, iov[i].iov_base, iov[i].iov_len) == -1) {
			perror("write");
			return EXIT_FAILURE;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int fd = open("testfile", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	char *wbuf1 = "hello\n";
	char *wbuf2 = "world\n";
	char *wbuf3 = "!\n";
	struct iovec *wiov = calloc(3, sizeof(struct iovec));
	wiov[0].iov_base = wbuf1;
	wiov[0].iov_len = 6;
	wiov[1].iov_base = wbuf2;
	wiov[1].iov_len = 6;
	wiov[2].iov_base = wbuf3;
	wiov[2].iov_len = 2;
	lwritev(fd, wiov, 3);
	free(wiov);

	lseek(fd, 0, SEEK_SET);

	char rbuf1[7];
	char rbuf2[7];
	char rbuf3[3];
	struct iovec *riov = calloc(3, sizeof(struct iovec));
	riov[0].iov_base = rbuf1;
	riov[0].iov_len = 6;
	riov[1].iov_base = rbuf2;
	riov[1].iov_len = 6;
	riov[2].iov_base = rbuf3;
	riov[2].iov_len = 2;

	lreadv(fd, riov, 3);

	rbuf1[6] = '\0';
	rbuf2[6] = '\0';
	rbuf3[2] = '\0';

	printf("rbuf1: %s\n", rbuf1);
	printf("rbuf2: %s\n", rbuf2);
	printf("rbuf3: %s\n", rbuf3);
	free(riov);

	return EXIT_SUCCESS;
}
