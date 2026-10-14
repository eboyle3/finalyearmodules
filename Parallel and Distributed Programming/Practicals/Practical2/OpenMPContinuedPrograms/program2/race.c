/*----------------------------------------------------
This program illustrates a simple example of a race
condition.

The variable amount is shared by both processes.
Amount is initialised to 100. One process performs
amount=amount+100, while the other performs
amount=amount+200.

What are the three possible final values of amount ?
Run it several times and see if you can produce all
three outputs. 
Notice also the output text. What is happening?
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

int amount, temp;

int main(int argc, char *argv[])
{
	amount=100;
		
	#pragma omp parallel default(shared) private(temp)
	{
		#pragma omp sections 
		{
			#pragma omp section
			{
				delay();
				temp=amount;
				printf("Sect 1: load on thread %d \n", omp_get_thread_num());
				delay();
				temp+=100;
				printf("Sect 1: add on thread %d \n", omp_get_thread_num());
				delay();
				amount=temp;
				printf("Sect 1: store on thread %d \n", omp_get_thread_num());
			}
		
			#pragma omp section
			{
				delay();
				temp=amount;
				printf("Sect 2: load on thread %d \n", omp_get_thread_num());
				delay();
				temp+=200;
				printf("Sect 2: add on thread %d \n", omp_get_thread_num());
				delay();
				amount=temp;
				printf("Sect 2: store on thread %d \n", omp_get_thread_num());
			}
		} /* end sections */
	} /* end parallel */
  	
	printf("amount = %i\n", amount);
	return 0;
}

