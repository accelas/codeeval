#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define MAX_DIM 16

static bool debug = false;

static struct matrix 
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

void show_col(struct idx *idx, int num)
{
	int i;
	printf("idx %d\n", idx->o);
	for (i = 0; i < num; i++) {
		printf("%4d\n", idx->v[i]);
	}
}

void show_matrix(struct matrix *m, bool final)
{
	int i;
	const int num = m->dim * m->dim; 
	if (!final)
		printf("dim %zu, data:\n", m->dim);
	for (i = 0; i < num; i++) {
		printf("%*d", final ? 0 : 4, m->data[i]);
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

	assert(num > 1);

	for (i = 0; i < num; i++) {
		idx_buf[i].o = i;
		copy_col_to(m, c_s + i, idx_buf[i].v);
	}

	cmp_row = r;
	qsort(idx_buf, num, sizeof(idx_buf[0]), cmp);

	for (i = 0; i < num; i++)
		copy_col_from(m, c_s + i, idx_buf[i].v);

}

void go(struct matrix *cur, int c_s, int c_e, int r)
{
	int i = c_s, j = i + 1;

	if (debug)
		printf("c_s %d c_e %d r %d\n", c_s, c_e, r);

	if (r >= cur->dim)
		return;

	if (debug) {
		printf("sorting row %d from column %d to %d\n", r, c_s , c_e - 1);
	}

	// sort current section
	sort(cur, c_s, c_e, r);

	if (debug) {
		printf("after sorting\n");
		show_matrix(cur, false);
		printf("\n");
	}

	while (i < c_e && j < c_e) {
		j = i + 1;

		if (debug)
			printf("i %d j %d r %d c_e %d \n", i, j, r, c_e);


		while (j < c_e) {
			assert (i < j);
			if (*at(cur, r, i) != *at(cur, r, j)) {
				if (j != i + 1)
					go(cur, i, j, r+1);
				i = j;
				break;
			}

			if (++j == c_e) // hitting the right edge
				go(cur, i, j, r+1);
		}
	}
	


#if 0
	// WTF: the 2 printf with i have different 'i'. (gcc 4.8 on ubuntu 14.04)
	// must be something wrong with closure or tail call elimination.
	// check child section of current range
	for (i = c_s, j = i + 1; i < c_e; i = j, j += 1) {
		printf("i %d %p j %d\n", i, &i, j);
		// move the right cursor, iff they're same
		for (j = i + 1; j < c_e; j++) {
			printf("i %d %p j %d\n", i, &i, j);
			if (*at(cur, r, i) != *at(cur, r, j)) {
				if (j == i + 1) {
					printf("next segment\n");
					break;
				}
				else {
					printf("going for %d to %d on row %d\n", i, j, r+1);
					go (cur, i, j, r + 1);
				}
			} // else continue move cursor
		}
	}
#endif
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
	if (debug)
		show_matrix(m, true);

	go(m, 0, m->dim, 0);

	show_matrix(m, true);
}

int main(int argc, const char * argv[])
{
    FILE *file = fopen(argv[1], "r");
    char line[1024];

    if (argc == 3)
        debug = true;

    while (fgets(line, 1024, file)) {
        proc_line(line);
    }

    return 0;
}

