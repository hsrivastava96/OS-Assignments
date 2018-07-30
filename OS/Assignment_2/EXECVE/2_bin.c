#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	int a[20], key, i, first, last, mid, flag;
	for(i=0; i<argc; i++)
	{
		a[i]=atoi(argv[i]);//atoi() function in C language converts string data type to int data type. 
	}
	printf("\nEnter the key you want to search in the array: ");
	scanf("%d", &key);
	first=0;
	last=i-1;
	while(1)
	{
		mid=(first+last)/2;
		if(a[mid]==key)
		{
			flag=1;
			break;
		}
		else if(a[mid]<key)
		{
		    first=mid+1;
		}
		else
		{
		    last=mid-1;
		}
	}
	if(flag==1)
		printf("\nElement %d was found at position %d in array! ", key, mid+1);
	else
		printf("\nElement not found !");
}
