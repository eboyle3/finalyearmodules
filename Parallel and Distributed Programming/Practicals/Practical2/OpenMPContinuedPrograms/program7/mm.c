/*------------------------------------------------------------------------------------------
This program multiplies two square matrices using 1..64 threads.

Be sure and try this in different execution environments (numbers of threads available)
------------------------------------------------------------------------------------------*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>               

int main (int argc, char *argv[]) 
{
	int	i, j, k, x, numthreads, ORDER;
	double start, end;
	double	** a;
	double	** b; 
	double	** c; 

	if(argv[1]==NULL)
	{
		printf("matrix order must be specified e.g. ./mm 500\n");
		return 1;
	}
	else 
	{
		ORDER = atoi(argv[1]);     
	}    

	/* Allocate pointer memory for the first dimension of a matrix[][]; */
	a = (double **) malloc(ORDER * sizeof(double *));
	if(NULL == a){free(a); printf("Memory allocation failed while allocating for a[].\n"); exit(-1);}
	
	b = (double **) malloc(ORDER * sizeof(double *));
	if(NULL == b){free(b); printf("Memory allocation failed while allocating for b[].\n"); exit(-1);}
	
	c = (double **) malloc(ORDER * sizeof(double *));
	if(NULL == c){free(c); printf("Memory allocation failed while allocating for c[].\n"); exit(-1);}

	/* Allocate integer memory for the second dimension of a matrix[][]; */
	for(x = 0; x < ORDER; x++)
	{
		a[x] = (double *) malloc(ORDER * sizeof(double));
		if(NULL == a[x]){free(a[x]); printf("Memory allocation failed while allocating for a[x][].\n"); exit(-1);}
		
		b[x] = (double *) malloc(ORDER * sizeof(double));
		if(NULL == b[x]){free(a[x]); printf("Memory allocation failed while allocating for b[x][].\n"); exit(-1);}

		c[x] = (double *) malloc(ORDER * sizeof(double));
		if(NULL == c[x]){free(a[x]); printf("Memory allocation failed while allocating for c[x][].\n"); exit(-1);}
	}

	/*** Initialize matrices ***/
	for (i=0; i<ORDER; i++)
		for (j=0; j<ORDER; j++)
			a[i][j]= i+j;

	for (i=0; i<ORDER; i++)
		for (j=0; j<ORDER; j++)
			b[i][j]= i*j;

	for (i=0; i<ORDER; i++)
		for (j=0; j<ORDER; j++)
			c[i][j]= 0;

	/*** Do matrix multiply sharing iterations on outer loop ***/
	printf(" matrix order is %i, # processors is %i", ORDER, omp_get_num_procs());
	printf("\n ---------------------------------------\n");

	for (numthreads=1; numthreads < 65; numthreads=numthreads*2)
	{
		start = omp_get_wtime();
		#pragma omp parallel for default(none) num_threads(numthreads) shared(a,b,c, ORDER) private(i,j,k)

		for (i=0; i<ORDER; i++)    
			for(j=0; j<ORDER; j++)       
				for (k=0; k<ORDER; k++)
					c[i][j] += a[i][k] * b[k][j];
	/*** End of parallel region ***/

	end = omp_get_wtime();
	printf(" %i threads: %f (secs)\n",numthreads, (end-start));
	}
}
