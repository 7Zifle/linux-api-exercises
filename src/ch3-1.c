#include <sys/reboot.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
#ifdef __FreeBSD__
	reboot(RB_AUTOBOOT);
#endif
	return 0;
}
