#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MOD 10000 + 7
typedef struct matrix
{
	int **mat;
	int line, column;
	int sum;
} matrix;
void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}
void increase_arraysize(matrix **array, int *capacity)
{
	*capacity *= 2;
	*array = realloc(*array, *capacity * sizeof(matrix));
}
void allocate_matrix(matrix *a)
{
	a->mat = malloc(a->line * sizeof(int *));
	for (int i = 0; i < a->line; i++)
		a->mat[i] = calloc(a->column, sizeof(int));
}
void read_matrix(matrix *a)
{
	for (int i = 0; i < a->line; i++)
		for (int j = 0; j < a->column; j++)
			scanf("%d", &a->mat[i][j]);
}
void print_matrix(matrix a)
{
	for (int i = 0; i < a.line; i++)
	{
		for (int j = 0; j < a.column; j++)
			printf("%d ", a.mat[i][j]);
		printf("\n");
	}
}
void freeone(matrix *a)
{
	for (int i = 0; i < a->line; i++)
		free(a->mat[i]);
	free(a->mat);
}
void freeall(matrix *a, int capacity)
{
	for (int i = 0; i < capacity; i++)
		freeone(&a[i]);
	free(a);
}
void supermegaswap(matrix *a, matrix *b)
{
	matrix aux;
	aux = *a;
	*a = *b;
	*b = aux;
}
void freeandresize(matrix **a, int *dimension, int k, int *capacity)
{
	for (int i = k; i < (*dimension) - 1; i++)
		supermegaswap(&(*a)[i], &(*a)[i + 1]);
	freeone(&(*a)[(*dimension) - 1]);
	(*dimension)--;
	// resize
	if (*dimension < *capacity / 2)
	{
		(*capacity) /= 2;
		*a = realloc(*a, *capacity * sizeof(matrix));
	}
}
void redimension(matrix *a)
{
	int n1, n2;
	int *lin, *col;
	matrix b;
	scanf("%d", &n1);
	lin = calloc(n1, sizeof(int));
	for (int i = 0; i < n1; i++)
		scanf("%d", &lin[i]);
	scanf("%d", &n2);
	col = calloc(n2, sizeof(int));
	for (int i = 0; i < n2; i++)
		scanf("%d", &col[i]);
	b.line = n1;
	b.column = n2;
	allocate_matrix(&b);
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++)
			b.mat[i][j] = a->mat[lin[i]][col[j]];
	supermegaswap(a, &b);
	free(lin);
	free(col);
	freeone(&b);
}
void inmultire(matrix *a, matrix *b, matrix *c)
{
	for (int i = 0; i < c->line; i++)
		for (int j = 0; j < c->column; j++)
			for (int k = 0; k < a->column; k++)
			{
				c->mat[i][j] += a->mat[i][k] * b->mat[k][j];
				while (c->mat[i][j] < 0)
					c->mat[i][j] += MOD;
				c->mat[i][j] %= MOD;
			}
}
void inmultireinplace(matrix *a, matrix *b)
{
	matrix aux;
	aux.line = a->line;
	aux.column = b->column;
	allocate_matrix(&aux);
	for (int i = 0; i < aux.line; i++)
		for (int j = 0; j < aux.column; j++)
			for (int k = 0; k < a->column; k++)
			{
				aux.mat[i][j] += a->mat[i][k] * b->mat[k][j];
				while (aux.mat[i][j] < 0)
					aux.mat[i][j] += MOD;
				aux.mat[i][j] %= MOD;
			}
	supermegaswap(a, &aux);
	freeone(&aux);
}
int sumof(matrix m)
{
	int s = 0;
	for (int i = 0; i < m.line; i++)
		for (int j = 0; j < m.column; j++)
			s += m.mat[i][j];
	while (s < 0)
		s += MOD;
	s %= MOD;
	return s;
}
void computeallsums(matrix *array, int dim)
{
	for (int i = 0; i < dim; i++)
		array[i].sum = sumof(array[i]);
}
void sortbysum(matrix *array, int dimension)
{
	int ok;
	do
	{
		ok = 1;
		for (int i = 0; i < dimension - 1; i++)
			if (array[i].sum > array[i + 1].sum)
				ok = 0, supermegaswap(&array[i], &array[i + 1]);
	} while (ok == 0);
}
void transpose(matrix *a)
{
	matrix b;
	b.line = a->column;
	b.column = a->line;
	allocate_matrix(&b);
	for (int i = 0; i < b.line; i++)
		for (int j = 0; j < b.column; j++)
			b.mat[i][j] = a->mat[j][i];
	supermegaswap(a, &b);
	freeone(&b);
}
void power(matrix *a, int exponent)
{
	matrix result, temp;
	result.line = a->line, result.column = a->column;
	allocate_matrix(&result);
	temp.line = result.line, temp.column = result.column;
	allocate_matrix(&temp);
	for (int i = 0; i < a->line; i++)
		for (int j = 0; j < a->column; j++)
			temp.mat[i][j] = a->mat[i][j];
	for (int i = 0; i < result.line; i++)
		for (int j = 0; j < result.column; j++)
			result.mat[i][j] = (i == j) ? 1 : 0;
	while (exponent > 0)
	{
		if (exponent % 2)
			inmultireinplace(&result, &temp);
		inmultireinplace(&temp, &temp);
		exponent /= 2;
	}
	supermegaswap(a, &result);
	freeone(&result);
	freeone(&temp);
}
int main(void)
{
	matrix *array;
	int capacity = 4, dimension = 0;
	char c;
	array = malloc(capacity * sizeof(matrix));
	while (scanf("%c", &c))
	{
		if (c == 'L')
		{
			if (dimension == capacity)
				increase_arraysize(&array, &capacity);
			scanf("%d %d", &array[dimension].line, &array[dimension].column);
			allocate_matrix(&array[dimension]);
			read_matrix(&array[dimension]);
			dimension++;
		}
		else if (c == 'P')
		{
			int k;
			scanf("%d", &k);
			if (k >= 0 && k < dimension)
				print_matrix(array[k]);
			else
				printf("No matrix with the given index\n");
		}
		else if (c == 'D')
		{
			int k;
			scanf("%d", &k);
			if (k >= 0 && k < dimension)
				printf("%d %d\n", array[k].line, array[k].column);
			else
				printf("No matrix with the given index\n");
		}
		else if (c == 'Q')
		{
			freeall(array, dimension);
			return 0;
		}
		else if (c == 'F')
		{
			int k;
			scanf("%d", &k);
			if (k >= 0 && k < dimension)
				freeandresize(&array, &dimension, k, &capacity);
			else
				printf("No matrix with the given index\n");
		}
		else if (c == 'C')
		{
			int k;
			scanf("%d", &k);
			if (k >= 0 && k < dimension)
				redimension(&array[k]);
			else
				printf("No matrix with the given index\n");
		}
		else if (c == 'M')
		{
			int k1, k2;
			scanf("%d %d", &k1, &k2);
			if (!((k1 >= 0 && k1 < dimension) && (k2 >= 0 && k2 < dimension)))
				printf("No matrix with the given index\n");
			else if (array[k1].column != array[k2].line)
				printf("Cannot perform matrix multiplication\n");
			else
			{
				if (dimension == capacity)
					increase_arraysize(&array, &capacity);
				array[dimension].line = array[k1].line,
				array[dimension].column = array[k2].column;
				allocate_matrix(&array[dimension]);
				inmultire(&array[k1], &array[k2], &array[dimension]);
				dimension++;
			}
		}
		else if (c == 'O')
		{
			computeallsums(array, dimension);
			sortbysum(array, dimension);
		}
		else if (c == 'T')
		{
			int k;
			scanf("%d", &k);
			if (k >= 0 && k < dimension)
				transpose(&array[k]);
			else
				printf("No matrix with the given index\n");
		}
		else if (c == 'R')
		{
			int k, pow;
			scanf("%d %d", &k, &pow);
			if (k < 0 || k >= dimension)
				printf("No matrix with the given index\n");
			else if (pow < 0)
				printf("Power should be positive\n");
			else if (array[k].column != array[k].line)
				printf("Cannot perform matrix multiplication\n");
			else
				power(&array[k], pow);
		}
		else if (isalpha(c))
			printf("Unrecognized command\n");
	}
}