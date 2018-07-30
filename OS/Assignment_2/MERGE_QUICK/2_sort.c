#include <stdio.h>
#include <sys/types.h>

void quicksort(int [20], int, int, int);
void merge(int [20],int ,int ,int );
void part(int [20],int ,int );

int main()
{
	int i;
	pid_t pid;
	int arr[20], arr1[20], sz, sz1;
	printf("\nEnetr number of elements for quicksort: ");
	scanf("%d", &sz);
	for(i=0; i<sz; i++)
	{
		printf("\nEnter element %d for array: ", i);
		scanf("%d", &arr[i]);
	}
	printf("\nEnetr number of elements for mergesort: ");
	scanf("%d", &sz1);
	for(i=0; i<sz1; i++)
	{
		printf("\nEnter element %d for array: ",i);
		scanf("%d", &arr1[i]);
	}
	pid=fork();
	if(pid==0)
	{
		printf("\nI'm child: %d", getpid());
		printf("\nMy parent is: %d", getppid());
		sleep(10);
		quicksort(arr, sz, 0, sz-1);
		printf("\n< - - - Sorted elements after quicksort - - - > \n");
	  	for(i=0; i<sz; i++)
	    	printf(" %d",arr[i]);
	    	printf("\n\n");

		printf("\n\n");
		
	}
	else
	{
		printf("\nI'm parent: %d", getpid());
		part(arr1, 0, sz1-1);
		printf("\n< - - - Merge sorted elements - - - >\n");
	 	for(i=0; i<sz1; i++)
	 	printf("%d ",arr1[i]);
	 	printf("\n\n");
		
		printf("\n\n");
		return 0;
	}
	return 0;
}

void quicksort(int arr[20], int sz, int first, int last)
{
	int pivot,j,temp,i;
	
	if(first<last)
	{
        	pivot=first;
         	i=first;
         	j=last;
	        while(i<j)
		{
             		while(arr[i]<=arr[pivot]&&i<last)
                 	i++;
	     	       	while(arr[j]>arr[pivot])
                 	j--;
	  	        if(i<j)
			{
                 		temp=arr[i];
                  		arr[i]=arr[j];
                  		arr[j]=temp;
             		}
         	}
         	temp=arr[pivot];
         	arr[pivot]=arr[j];
         	arr[j]=temp;
         	quicksort(arr,sz,first,j-1);
         	quicksort(arr,sz,j+1,last);
    	}
}

void part(int arr1[],int min,int max)
{
	int mid;
 	if(min<max)
 	{
   		mid=(min+max)/2;
   		part(arr1,min,mid);
   		part(arr1,mid+1,max);
   		merge(arr1,min,mid,max);
 	}
}

void merge(int arr1[],int min,int mid,int max)
{
	int tmp[30];
  	int i,j,k,m; 
  	j=min;
  	m=mid+1;
  	for(i=min; j<=mid && m<=max ; i++)
  	{
     		if(arr1[j]<=arr1[m])
     		{
         		tmp[i]=arr1[j];
         		j++;
     		}
     		else
     		{
         		tmp[i]=arr1[m];
         		m++;
     		}
  	}
  	if(j>mid)
  	{
     		for(k=m; k<=max; k++)
     		{
         		tmp[i]=arr1[k];
         		i++;
     		}
  	}
  	else
  	{
     		for(k=j; k<=mid; k++)
     		{
        		tmp[i]=arr1[k];
        		i++;
     		}
  	}
  	for(k=min; k<=max; k++)
     		arr1[k]=tmp[k];
}
