/*--------------------------------------------------------------------------
This program illustrates the random nature of process
scheduling.

1. Run 
   $./scheduler 1 
   several times and compare the output.

2. Repeat using 
   $./scheduler 2
   and then 
   $./scheduler 3 
   Using
   $./scheduler 2 | sort
   may help you understand what is going on.

3. Now experiment by varying the number of threads through the environment variable OMP_NUM_THREADS,
   for example, 
   $export OMP_NUM_THREADS=3
---------------------------------------------------------------------------*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

/* A simple delay loop */
void delay()
{
	int i;
	float a=10000.0;
	unsigned int iseed = (unsigned int)time(NULL);
	srand (iseed);
	for (i=0; i < rand(); i++)
		a=1.0/sqrt(a); 
}

int main(int argc, char *argv[])
{
	int i, j, branch;

	if(argv[1]==NULL)
	{
		printf("1, 2, 3 or 4 must be specified as an argument\n");
  		return 1;
	}
	else 
	{
		branch = atoi(argv[1]);     
	} 

	printf(" using %i processors\n -------------------\n", omp_get_num_procs());

	switch (branch) 
	{
	case 1: {
			printf("\n#pragma omp parallel for default(shared) private(i,j)\n");
			printf("-----------------------------------------------------\n");
			#pragma omp parallel for default(shared) private(i,j) 
				for (i=0; i<19; i++)
				{
					printf("Thread %i, index %i\n",omp_get_thread_num(), i);
					for (j=0; j<i; j++)
						delay();
				}
			break;
			}
	case 2: {
			printf("\n#pragma omp parallel for default(shared) private(i,j) schedule(static,2)\n");
			printf("------------------------------------------------------------------------\n");
			#pragma omp parallel for default(shared) private(i,j) schedule(static,2)
				for (i=0; i<19; i++)
				{
					printf("Thread %i, index %i\n",omp_get_thread_num(), i);
					for (j=0; j<i; j++)
						delay();
				}
			break;
			}
	case 3: {
			printf("\n#pragma omp parallel for default(shared) private(i,j) schedule(dynamic,2)\n");
			printf("-------------------------------------------------------------------------\n");
			#pragma omp parallel for default(shared) private(i,j) schedule(dynamic,2)
				for (i=0; i<19; i++)
				{   
					printf("Thread %i, index %i\n",omp_get_thread_num(), i);
					for (j=0; j<i; j++)
						delay();
				}
			break;
			}
	case 4: {
			printf("\n#pragma omp parallel for ordered default(shared) private(i,j) schedule(dynamic,2)\n");
			printf("----------------------------------------------------------------------------------\n");
			#pragma omp parallel for ordered default(shared) private(i,j) schedule(dynamic,2)
				for (i=0; i<19; i++)
				{   
					for (j=0; j<i; j++)
						delay();
					#pragma omp ordered
					{printf("Thread %i, index %i\n",omp_get_thread_num(), i);}
				}
			break;
			}
	}
	return 0;
}

