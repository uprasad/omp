#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("1 argument\n");
		return 0;
	}
	
	int N = atoi(argv[1]);
	double sqN = sqrt(N);
	
	int *A = (int*)malloc(N*sizeof(int));
	
	int i, j;
	for (i=0; i<N; ++i)
		A[i] = 1;
		
	A[0] = 0;
	A[1] = 0;
	
	for (i=2; i<=sqN; ++i)
	{
		if (A[i] != 1)
			continue;
		for (j=2; i*j<N; ++j)
		{
//			printf("i*j = %d\n", i*j);
			A[i*j] = 0;
		}
//		printf("\n");
	}
	
	int count = 0;
	for (i=0; i<N; ++i)
		count += A[i];
		
	printf("%d\n", count);
	
	return 0;
}
