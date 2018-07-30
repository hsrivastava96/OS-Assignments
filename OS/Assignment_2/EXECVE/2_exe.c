#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>//unistd.h is the C/C++ header file that is your code's entry point to various constant, type and function declarations that comprise the POSIX operating system API.
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void bubblesort(int a[20], int n)
{
	int d,swap,c,i;
	for (c=0; c<(n-1); c++)
  	{
    		for (d=0; d<n-c-1; d++)
    		{
      			if (a[d]>a[d+1])
      			{
        			swap = a[d];
        			a[d] = a[d+1];
        			a[d+1] = swap;
      			}
    		}
  	}
  	
}

int main()
{
	pid_t pp_id, par_id, c_id, id;
	int a[20], i, n;
	char *arg[20], str[20];
	printf("\nEnter the number of elements in the array: ");
	scanf("%d", &n);
	printf("\nEnter the elements of the array: ");
	for(i=0; i<n; i++)
	{
		scanf("%d", &a[i]);
	}
	bubblesort(a, n);
	
	pp_id=getpid();
	id=fork();
	if(id==0)
	{
		printf("\n\nSorted array is: ");	
		for(i=0; i<n; i++)
		{
			printf(" %d ", a[i]);
		}
		c_id=getpid();
		printf("\nI'm child with id --> %d", c_id);
		par_id=getppid();
		printf("\nMy parent's id is --> %d", par_id);
		for(i=0; i<n; i++)
		{
			sprintf(str, "%d", a[i]);//int sprintf(char *str, const char *format, ...) sends formatted output to a string pointed to, by str.
			arg[i]=malloc(sizeof(str));
			strcpy(arg[i], str);
		}
		arg[i]=NULL;
		execve("./binsrch.out", arg, NULL);
		exit(0);
	}
	else
	{
		wait();
		printf("\nI'm parent with id --> %d\n\n", pp_id);
	}
	return 0;
}

