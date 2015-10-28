#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int acc[26];

int calc(void)
{
   int sum = 0;
   int i;

   for (i = 0; i < 26; i++) {
        sum += acc[i] * (26 - i);
   }
   return sum;
}

int cmp(const void *p1, const void *p2) {
	return ((*(const int *)p2) - (*(const int *)p1));
}

void parse(char *str)
{
    char *p, q;
    int i;

    for (p = str; *p ; p++) {
        q = *p;
        if ('A' <= q && q <= 'Z')
            q -= 'A';
        else if ('a' <= q && q <= 'z')
            q -= 'a';
        else
            continue;
        acc[q]++;
    }
    qsort(acc, 26, sizeof(acc[0]), cmp);
}

void proc_line(char *line)
{
    int res;

    memset(acc, 0 , sizeof(acc));
    parse(line);
    res = calc();

    printf("%d\n", res);
}

int main(int argc, const char * argv[])
{
    FILE *file = fopen(argv[1], "r");
    char line[1024];

    while (fgets(line, 1024, file)) {
        proc_line(line);
    }

    return 0;
}
