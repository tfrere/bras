#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int open_port(void)
{
	int fd;                                   /* File descriptor for the port */

	fd = open("/dev/ttyACM1", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{                                              /* Could not open the port */
		fprintf(stderr, "open_port: Unable to open /dev/ - %d\n",
				strerror(errno));
	}
	return (fd);
}

char read_myo_data(char *raw_data)
{
	if (raw_data)
		return (3);
	return (0);
}

int send_to_arduino(char *buf, int fd)
{
	char		byte;

	byte = read_myo_data(buf);
	write(fd, &byte, 1);
}

int main(void)
{
	int fd2;
	char buf[512];

	fd2 = open_port();
	while (1)
	{
		scanf(%s, buf);
		send_to_arduino(buf, fd2);
	}
	return (0);
}
