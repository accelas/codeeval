#include <string.h>
#include <stdio.h>
#include <stdlib.h>

inline char toLower(char c) 
{
	if ('A' <= c && c <= 'Z')
		return c + ('a' - 'A');
	return c;
}

int main(int argc, char *argv[])
{
	FILE *f;
	char c;

	if (argc != 2) {
		printf("Usage:\n");
		printf("  %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	f = fopen(argv[1], "r");
	if (!f) {
		perror(NULL);
		exit(EXIT_FAILURE);
	}

	while ((c = fgetc (f)) != EOF)
		printf("%c", toLower(c));

	fclose(f);

	exit(EXIT_SUCCESS);
}
