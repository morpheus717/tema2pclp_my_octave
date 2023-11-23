#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INC 4
#define MOD 10000 + 7
void upload_matrix(int ***p, int n, int m, int index)
{
	p[index] = malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		p[index][i] = calloc(m, sizeof(int));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &p[index][i][j]);
}
void print_matrix(int ***p, int *n, int *m, int index)
{
	for (int i = 0; i < n[index]; i++)
	{
		for (int j = 0; j < m[index]; j++)
			printf("%d ", p[index][i][j]);
		printf("\n");
	}
}
void redimension(int ***mat, int *n, int *m, int index)
{
	int *line, *column, l, c, **copy;
	scanf("%d", &l);
	line = malloc(l * sizeof(int));
	for (int i = 0; i < l; i++)
		scanf("%d", &line[i]);
	scanf("%d", &c);
	column = malloc(c * sizeof(int));
	for (int j = 0; j < c; j++)
		scanf("%d", &column[j]);
	// copiez matricea
	copy = malloc(n[index] * sizeof(int *));
	for (int i = 0; i < n[index]; i++)
		copy[i] = malloc(m[index] * sizeof(int));
	for (int i = 0; i < n[index]; i++)
		for (int j = 0; j < m[index]; j++)
			copy[i][j] = mat[index][i][j];
	mat[index] = realloc(mat[index], l * sizeof(int *));
	for (int i = 0; i < l; i++)
		mat[index][i] = realloc(mat[index][i], c * sizeof(int));
	for (int i = 0; i < l; i++)
		for (int j = 0; j < c; j++)
			mat[index][i][j] = copy[line[i] - 1][column[j] - 1];
	for (int i = 0; i < n[index]; i++)
		free(copy[i]);
	free(copy);
	n[index] = l;
	m[index] = c;
}
void multiply_matrix(int ***mat, int k1, int k2, int index, int *n, int *m)
// sirul de matrice, indice matr A, indice matr B, indice C, linii, coloane
// C = A x B
{
	n = realloc(n, (index + 1) * sizeof(int));
	m = realloc(m, (index + 1) * sizeof(int));
	n[index] = n[k1];
	m[index] = m[k2];
	mat = realloc(mat, (index + 1) * sizeof(int **));
	mat[index] = malloc(n[index] * sizeof(int *));
	for (int i = 0; i < n[index]; i++)
		mat[index][i] = calloc(m[index], sizeof(int));
	for (int i = 0; i < n[k1]; i++)
		for (int j = 0; j < m[k2]; j++)
			for (int k = 0; k < m[k1]; k++)
				mat[index][i][j] += mat[k1][i][k] * mat[k2][k][j];
}
int sumofmatrix(int **p, int n, int m)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			sum += p[i][j] % MOD;
	return sum;
}
void swapmatrix(int **p1, int **p2, int l1, int c1, int l2, int c2)
{
	int **aux;
	aux = malloc(l1 * sizeof(int *));
	for (int i = 0; i < l1; i++)
		aux[i] = calloc(c1, sizeof(int));
	for (int i = 0; i < l1; i++)
		for (int j = 0; j < c1; j++)
			aux[i][j] = p1[i][j];
	p1 = realloc(p1, sizeof(int *) * l2);
	for (int i = 0; i < l2; i++)
		p1[i] = realloc(p1[i], c2 * sizeof(int));
	for (int i = 0; i < l2; i++)
		for (int j = 0; j < c2; j++)
			p1[i][j] = p2[i][j];
	for (int i = 0; i < l1; i++)
		for (int j = 0; j < c1; j++)
			p2[i][j] = aux[i][j];
	for (int i = 0; i < l1; i++)
		free(aux[i]);
	free(aux);
}
void sortbysum(int ***p, int n, int *l, int *c)
{
	int *sums, ok;
	sums = calloc(n, sizeof(int));
	for (int i = 0; i < n; i++)
		sums[i] = sumofmatrix(p[i], l[i], c[i]);
	do
	{
		ok = true;
		for (int i = 0; i < n - 1; i++)
			if (sums[i] > sums[i + 1])
			{
				ok = false;
				int aux = sums[i];
				sums[i] = sums[i + 1];
				sums[i + 1] = aux;
				swapmatrix(p[i], p[i + 1], l[i], c[i], l[i + 1], c[i + 1]);
			}
	} while (ok = false);
}
void transpune(int ***p, int *n, int *m, int k)
{
	int **aux, n2, m2;
	n2 = m[k];
	m2 = n[k];
	aux = malloc(n2 * sizeof(int *));
	for (int i = 0; i < n2; i++)
		aux[i] = calloc(m2, sizeof(int));
	for (int i = 0; i < n[k]; i++)
		for (int j = 0; j < m[k]; j++)
			aux[i][j] = p[k][i][j];
	p[k] = realloc(p[k], n2 * sizeof(int *));
	for (int i = 0; i < n2; i++)
		p[k][i] = realloc(p[k][i], m2 * sizeof(int));
	for (int i = 0; i < n2; i++)
		for (int j = 0; j < m2; j++)
			p[k][j][i] = aux[i][j];
}
void power(int ***p, int *n, int *m, int k)
{
	
}
int main(void)
{
	int ***mat, index = 0, dim = INC, *n, *m;
	char c;
	mat = malloc(dim * sizeof(int **));
	n = calloc(dim, sizeof(int));
	m = calloc(dim, sizeof(int));
	dim += INC;
	while (scanf("%c", &c) != EOF)
	{
		if (dim == index)
		{
			dim += INC;
			mat = realloc(mat, dim * sizeof(int **));
			n = realloc(n, dim * sizeof(int));
			m = realloc(m, dim * sizeof(int));
		}
		if (c == 'L')
		{
			scanf("%d %d", &n[index], &m[index]);
			upload_matrix(mat, n[index], m[index], index);
			// print_matrix(mat[index], n[index], m[index]);
			index++;
		}
		if (c == 'D')
		{
			int k;
			scanf("%d", &k);
			if (n[k] == 0 || m[k] == 0)
				printf("No matrix with the given index\n");
			else
				printf("%d %d\n", n[k], m[k]);
		}
		if (c == 'P')
		{
			int k;
			scanf("%d", &k);
			if (n[k] == 0 || m[k] == 0)
				printf("No matrix with the given index\n");
			else
				print_matrix(mat, n, m, k);
		}
		if (c == 'C')
		{
			int k;
			scanf("%d", &k);
			if (n[k] == 0 || m[k] == 0)
				printf("No matrix with the given index\n");
			else
				redimension(mat, n, m, k);
		}
		if (c == 'M')
		{
			int k1, k2;
			scanf("%d%d", &k1, &k2);
			if (n[k1] == 0 || m[k1] == 0 || m[k1] == 0 || m[k2] == 0)
				printf("No matrix with the given index\n");
			else if (m[k1] != n[k2])
				printf("Cannot perform matrix multiplication\n");
			else
			{
				multiply_matrix(mat, k1, k2, index, n, m);
				print_matrix(mat, n, m, index);
				printf("%d %d\n", n[index], m[index]);
				index++;
			}
		}
		if (c == 'O')
			sortbysum(mat, index, n, m);
		if (c == 'T')
		{
			int k;
			scanf("%d", &k);
			transpune(mat, n, m, k);
		}
	}
}