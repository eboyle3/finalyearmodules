/*----------------------------------------------------
A simple program to illustrate interleaving. 
Two parallel sections with shared variables c1 and c2 
in one section c1=c1*c2                             
in one section c1=c1+c2                             
Run it several times and observe the output.
Repeat with the delay statements commented out. 
-------------------------------------------------------*/
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
	int c1=2, c2=3, temp;
	printf(" using %i processors\n -------------------\n", omp_get_num_procs());
	#pragma omp parallel default(shared) private(temp)
	{
		#pragma omp sections 
    		{
			#pragma omp section
			{
				delay();
				c1=c1*c2; 
				delay();
				printf(" thread %i finished\n", omp_get_thread_num());
			} /* end section */
			
			#pragma omp section
			{
				delay();
				c1=c1+c2; 
				delay();
				printf(" thread %i finished\n", omp_get_thread_num());
			}
  		} /* end sections */
	} /* end parallel */

	delay();
	printf(" c1 = %i\n", c1);
	
	return 0;
}