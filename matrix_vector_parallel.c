#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP	
	#include <omp.h>
#else
	#define omp_get_num_threads() 0
	#define omp_get_thread_num() 0
#endif

void mxv(int m, int n, double* restrict a, double* restrict b, double* restrict c);

int main(int argc, char **argv)
{
	int i, j;
	int m, n;
	double *a, *b, *c;
	
	if (argc < 4)
		return -1;
		
	printf("%d\n", atoi(argv[3]));
	omp_set_num_threads(atoi(argv[3]));
	
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
	
	#pragma omp parallel for default(none) \
		shared(m, n, b) private(i, j)
	for (i=0; i<m; ++i)
	{
		for (j=0; j<n; ++j)
			b[i*n+j] = i;
	} /*-- End of omp parallel for --*/
	
	printf("Exec mxv\n");
	
	mxv(m, n, a, b, c);
	printf("Done\n");
	
	free(a); free(b); free(c);
		
	return 0;
}

void mxv(int m, int n, double* restrict a, double* restrict b, double* restrict c)
{
	int i, j;
	
	#pragma omp parallel shared(m, n, a, b, c) private(i, j)
	{
		#pragma omp for
		for (i=0; i<m; ++i)
		{
			printf("%d, %d\n", i, omp_get_thread_num());
			a[i] = 0;
			for (j=0; j<n; ++j)
				a[i] += b[i*n+j]*c[j];
		} /*-- End of omp parallel for --*/
	}
}	
