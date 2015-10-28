
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_DIM 16

struct matrix 
{
	size_t dim;
	int data[MAX_DIM * MAX_DIM];
} data_buf;

static struct idx { 
	int o; 
	int v[MAX_DIM];
} idx_buf[MAX_DIM];

int *at(struct matrix *m, int r, int c)
{
	return &m->data[r*m->dim+c];
}

void show_col(struct idx *idx, int num) {
	int i;
	printf("idx %d\n", idx->o);
	for (i = 0; i < num; i++) {
		printf("%d\n", idx->v[i]);
	}

}

void show_matrix(struct matrix *m, bool final)
{
	int i;
	const int num = m->dim * m->dim; 
	if (!final)
		printf("dim %zu, data:\n", m->dim);
	for (i = 0; i < num; i++) {
		printf("%d", m->data[i]);
		if ((i + 1) == num)
			printf("\n");
		else if ((i + 1 ) % m->dim == 0)
			printf("%s", final ? " | " : "\n");
		else
			printf(" ");
	}
}

void copy_col_to(struct matrix *src, int c, int *dst)
{
	for (int i = 0; i < src->dim; i++)
		dst[i] = *at(src, i, c);
}

void copy_col_from(struct matrix *dst, int c, int *src)
{
	for (int i = 0; i < dst->dim; i++)
		 *at(dst, i, c) = src[i];
}

static int cmp_row = 0;

int cmp(const void *p1, const void *p2) {
	return (((const struct idx *)p1)->v[cmp_row] - ((const struct idx *)p2)->v[cmp_row]);
}

static int sort_counter = 0;
void sort(struct matrix *m, int c_s, int c_e, int r)
{
	int i;
	const size_t num = c_e - c_s;
	printf("sort %d\n", sort_counter++);
	show_matrix(m, false);

	for (i = 0; i < num; i++) {
		idx_buf[i].o = i;
		copy_col_to(m, c_s + i, idx_buf[i].v);
	}

	cmp_row = r;
	qsort(idx_buf, num, sizeof(idx_buf[0]), cmp);

	for (i = 0; i < num; i++)
		copy_col_from(m, c_s + i, idx_buf[i].v);
	show_matrix(m, false);

}

void go(struct matrix *cur, int c_s, int c_e, int r)
{
	int j = 1;

	// sort current section
	sort(cur, c_s, c_e, r);

	// check child section of current range
	for (int i = c_s; i < c_e; i += j) {
		// move the right cursor, iff they're same
		for (j = 1; j < c_e - i; j++) {
			if (*at(cur, r, i) != *at(cur, r, i + j)) {
				if (j == 1) // two cursor's are different
					goto next; // advance left cursor
				else
					go (cur, i, i + j + 1, r + 1);
			} // else continue move cursor
		}
next: {}
	}
}

void proc_line(char *line)
{
	int i;
	char *p, *q;
	struct matrix *m = &data_buf;

	memset(m, 0, sizeof(*m));

	// clean '|'
	p = line;
	while ((p = strchr(p , '|')) != NULL)
		*p = ' ';

	p = line;

	for (i = 0; i < MAX_DIM * MAX_DIM; i++) {
		m->data[i] = strtol(p, &q, 0);
		
		if (p == q)
			break;
		p = q;
	}

	m->dim = sqrt(i);

	sort_counter = 0;
	go(m, 0, m->dim, 0);

	show_matrix(m, true);
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

