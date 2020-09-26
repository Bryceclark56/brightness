#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char* argv[])
{
	const char* file_path = "/sys/class/backlight/intel_backlight/brightness";
	size_t arg1_size;
	int fd;

	arg1_size = strlen(argv[1]);

	if (strncmp(argv[1], "0", arg1_size) == 0) {
		fprintf(stderr, "Cannot set brightness to 0\n");
		return EXIT_FAILURE;
	}

	fd = open(file_path, O_WRONLY);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	printf("Writing %s to brightness file\n", argv[1]);
	if (write(fd, argv[1], arg1_size) == -1) {
		perror("write");
		return EXIT_FAILURE;
	}

	if (close(fd) == -1) {
		perror("close");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
