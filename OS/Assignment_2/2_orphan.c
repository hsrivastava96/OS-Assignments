# include <stdio.h> 
int main()
{ 
	int pid;
	pid=getpid(); 
	printf("Current Process ID is : %d\n",pid); 
	printf("\n[Forking Child Process ... ] \n"); 
	pid=fork(); /* This will Create Child Process and Returns Child's PID */
	if(pid < 0) 
	{ 			
		printf("\nProcess can not be created ");
		//exit(-1); 
	} 
	else
	{
        	if(pid==0)
		{ /* Child Process */
			printf("\nChild Process is Sleeping ..."); 
			sleep(5); /*Orphan Child's Parent ID is 1 */
			printf("\nOrphan Child's Parent ID : %d",getppid()); 
		}
 
		else
		{ /* Parent Process */
			printf("\nParent Process Completed ..."); 
		} 
	}
	return 0; 
}

