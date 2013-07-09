#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("2 arguments\n");
		return 0;
	}
	
	omp_set_num_threads(atoi(argv[2]));
	
	int N = atoi(argv[1]);
	int sqN = (int)sqrt(N);
	
	int *A = (int*)malloc(N*sizeof(int));
	
	int i, j;
	for (i=0; i<N; ++i)
		A[i] = 1;
		
	A[0] = 0;
	A[1] = 0;
	
	#pragma omp parallel for schedule(dynamic) shared(A, sqN, N) private(i, j)
	for (i=2; i<=sqN; ++i)
	{
		if (A[i] != 1)
			continue;
		for (j=2; i*j<N; ++j)
		{
			A[i*j] = 0;
		}
	}
	
	int count = 0;
	for (i=0; i<N; ++i)
		count += A[i];
		
	printf("%d\n", count);
	
	return 0;
}
