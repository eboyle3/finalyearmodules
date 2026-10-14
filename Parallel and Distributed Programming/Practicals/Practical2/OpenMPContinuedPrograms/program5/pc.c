/*------------------------------------------------------------
First, the producer adds an element to the buffer. 
A new element can be added to the buffer only after the previous 
element added has been read by one and only one of the consumers.

1. Run the program several times and observe whether it satisfies the 
specification.

Using ./pc | sort may help understand what is happening.

2. Using a suitable critical section modify the program so that
it meets the specification.

3. Modify the program so that,
first, the producer adds an element to the buffer, then 
a new element is added to the buffer when the previous 
element added has been read by both of the consumers.
------------------------------------------------------------*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#define MAX 10

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
	int buffer;
	int i;
	
	printf(" using %i processors\n -------------------\n", omp_get_num_procs());
	
	#pragma omp parallel default(shared) num_threads(3)
	{
		#pragma omp sections 
		{
			#pragma omp section /* producer */
			{
				delay();
		
				for (i=0; i<MAX; i++)
				{
					delay();
					buffer=i;
				        printf(" Producer puts %i in buffer\n", i);
				        delay();
				}
			} /* end producer */

			#pragma omp section /* consumer 1 */
			{
				delay();
				while (i<MAX)
			      	{
					delay();
        				printf(" consumer 1 gets %i from buffer\n", buffer);
				        delay();
				}
			} /* end consumer 1 */

			#pragma omp section /* consumer 2*/
			{
				delay();
			
				while (i<MAX)
				{
					delay();
				        printf(" consumer 2 gets %i from buffer\n", buffer);
				        delay();
				}
			} /* end consumer 2 */
		} /* end sections */
	} /* end parallel */

	return 0;
}

