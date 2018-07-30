#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include<stdio.h>

int main()
{ 
	int pid;
	pid=getpid(); 
	printf("Current Process ID is : %d\n",pid); 
	printf("[ Forking Child Process ... ] \n"); 
	pid=fork(); /* This will Create Child Process and Returns Child's PID */
	if(pid < 0) 
	{ 			
		printf("Process can not be created ");
		//exit(-1); 
	} 
       	if(pid > 0)
	{ 
			printf("PRENT  Process is sleeping ..."); 
			sleep(5); /*Orphan Child's Parent ID is 1 */
			printf("\nID : %d",getppid()); 
	}
 	else
	{ 
		exit(0);
	} 
	return 0; 
}

