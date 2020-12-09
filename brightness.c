#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void read_brightness();
void write_brightness();
FILE* open_file(const char* mode);

const char* DEFAULT_FILE_PATH = "/sys/class/backlight/intel_backlight/brightness";

int main(int argc, const char* argv[])
{
	if (argc == 1) {
		read_brightness();
	}
	else {
		write_brightness(argv[1]);
	}

	return 0;
}

void read_brightness()
{
	FILE * file = open_file("r");
	int value;

	fscanf(file, "%d", &value);

	printf("%d\n", value);
}

void write_brightness(const char* value)
{
	FILE * file = open_file("w");
	int result;
	size_t value_size = strlen(value) + 1;

	result = fprintf(file, "%s", value);

	if (result < 0) {
		perror("fprintf");
	}
	else if ((size_t)result != value_size) {
		printf("Something went wrong while writing to file");
	}

	
}

FILE* open_file(const char* mode)
{
	FILE * file = NULL;

	file = fopen(DEFAULT_FILE_PATH, mode); 
	if (file == NULL) {
		int errnum = errno;
		perror("fopen");
		exit(errnum);
	}

	return file;
}
