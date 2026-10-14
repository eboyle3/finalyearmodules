/*----------------------------------------------------
A Bank has 10,000 savings accounts each with 1000.
The total assets are threfore 10,000,000.
The automatic teller machine(ATM) continuously picks two
accounts at random and adds 500 to one and deducts 500
from the other. The totals assets should therefore remain
at 10,000,000. Perodically the auditor sums the Bank's assets
and outputs the total.

The correct operation is now ensured by using a critical
section.
-------------------------------------------------------*/
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#define length 10000
int account[length];

void initialize()
{
	/* initialize bank account */
	int i;
	
	for (i=0; i<length; i++)
		account[i] = 1000;
}

void withdraw(int index, int amount)
{
	account[index]=account[index]-amount;
}

void deposit(int index, int amount)
{
	account[index]=account[index]+amount;
}

void audit()
{
	int count, j;
	count=0;
	
	for (j=0; j<length;j++)
		count+=account[j];

	printf(" account total = %i\n", count);
}

int main(int argc, char *argv[])
{
	int i, j, random_int;
	printf(" using %i processors\n -------------------\n", omp_get_num_procs());
	
	initialize();

	#pragma omp parallel default(shared) private(i,j, random_int)
	{
		#pragma omp sections 
		{
			#pragma omp section
    			{
				for (i=0; i<100000; i++)
      				{
					#pragma omp critical (bank)
					{
						random_int = rand()%1000;
						withdraw(random_int, 500);
						random_int = rand()%1000;
						deposit(random_int,500);
					}
      				}
			}

			#pragma omp section
    			{
				for (i=0; i<10; i++)
				{
					#pragma omp critical (bank)
				        {
				        	audit();
					}
      				}
    			}
		} /* end sections */

	} /* end parallel */
	
	return 0;
}

