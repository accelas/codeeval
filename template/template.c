#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void solution(File *f)
{
	// parse the input
	
	// work
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

	solution(f);

	exit(EXIT_SUCCESS);
}
