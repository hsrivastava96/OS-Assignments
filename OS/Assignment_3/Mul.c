#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int a[10][10], b[10][10], c[10][10], k=0;

struct nod
{
	int i, j;
};
typedef struct nod node;

void * mulfunc(void * dat)
{
	node *data=dat;
	int sum=0, n=0;			//Here, n is the Kth index which remains constant while multiplying between two matrices
	for(n=0; n<k; n++)
		sum+=a[data->i][n]*b[n][data->j];
	c[data->i][data->j]=sum;
	pthread_exit(0);
}

void accept(int arr[10][10], int row, int col)
{
	int i=0, j=0;
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
			printf("\nValue at [%d][%d] --> ", i, j);
			scanf("%d", &arr[i][j]);
		}
	}
}

void display(int arr[10][10], int row, int col)
{
	int i=0, j=0;
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
			printf("%d\t", arr[i][j]);
		printf("\n");
	}
}

int main()
{
	int r1, r2, c1, c2, i=0, j=0;
	printf("\nPlease enter no. of rows in matrix 1 --> ");
	scanf("%d", &r1);
	printf("\nPlease enter no. of columns in matrix 1 --> ");
	scanf("%d", &c1);
	printf("\nPlease enter no. of rows in matrix 2 --> ");
	scanf("%d", &r2);
	printf("\nPlease enter no. of columnss in matrix 2 --> ");
	scanf("%d", &c2);
	if(c1==r2)
	{
		printf("\nPlease enter values in matrix 1\n");
		accept(a, r1, c1);
		printf("\nPlease enter values in matrix 1\n");
		accept(b, r2, c2);
	}
	else
	{
		printf("Wrong inputs. Please make sure that columns of matrix 1 = rows of matrix 2.\n");
		printf("Please enter no. of rows in matrix 1 --> ");
		scanf("%d", &r1);
		printf("Please enter no. of columns in matrix 1 --> ");
		scanf("%d", &c1);
		printf("Please enter no. of rows in matrix 2 --> ");
		scanf("%d", &r2);
		printf("Please enter no. of columnss in matrix 2 --> ");
		scanf("%d", &c2);
		printf("\nPlease enter values in matrix 1\n");
		accept(a, r1, c1);
		printf("\nPlease enter values in matrix 1\n");
		accept(b, r2, c2);
	}
	k=c1;
	for(i=0; i<r1; i++)
	{
		for(j=0; j<c2; j++)
		{
			node *data=(node *)malloc(sizeof(node));
			data->i=i;
			data->j=j;
			pthread_t tid;
			pthread_create(&tid, NULL, mulfunc, data);
			pthread_join(tid, NULL);	
		}
	}
	printf("\n\t\t----------------------------\n");
	printf("\n\t\t**********Matrix 1**********\n");
	printf("\n\t\t----------------------------\n");
	display(a, r1, c1);
	printf("\n\t\t----------------------------\n");
	printf("\n\t\t**********Matrix 2**********\n");
	printf("\n\t\t----------------------------\n");
	display(b, r2, c2);
	printf("\n\t\t----------------------------------\n");
	printf("\n\t\t**********Product Matrix**********\n");
	printf("\n\t\t----------------------------------\n");
	display(c, r1, c2);
	return 0;
}
