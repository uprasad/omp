#include <stdio.h>
#include <stdlib.h>

void mxv(int m, int n, double* restrict a, double* restrict b, double* restrict c);

int main(int argc, char **argv)
{
	int i, j;
	int m, n;
	double *a, *b, *c;
	
	if (argc < 3)
		return -1;
	
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	
	if ((a = (double*)malloc(m*sizeof(double))) == NULL)
		perror("mem alloc a");
	if ((b = (double*)malloc(m*n*sizeof(double))) == NULL)
		perror("mem alloc a");
	if ((c = (double*)malloc(n*sizeof(double))) == NULL)
		perror("mem alloc a");
		
	printf("Init b and c\n");
	
	for (i=0; i<n; ++i)
		c[i] = 2.0;
	for (i=0; i<m; ++i)
		for (j=0; j<n; ++j)
			b[i*n+j] = i;
	
	printf("Exec mxv\n");
	
	mxv(m, n, a, b, c);
	printf("Done\n");
	
	free(a); free(b); free(c);
		
	return 0;
}

void mxv(int m, int n, double* restrict a, double* restrict b, double* restrict c)
{
	int i, j;
	for (i=0; i<m; ++i)
	{
		a[i] = 0;
		for (j=0; j<n; ++j)
			a[i] += b[i*n+j]*c[j];
	}
}	
