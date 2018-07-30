#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

int count=0, in=0, out=0, buffer[5];
sem_t full, empty;
pthread_mutex_t m;

void * producer(void * t_num)
{
	int thread_num=*(int *)t_num;
	while(1)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&m);
		if(count>=5)
			printf("\nBUFFER FULL!!!\n");
		else
		{
			buffer[in]=rand()%100;
			printf("\nPRODUCER %d has produced: %d\n", thread_num, buffer[in]);
			in=(in+1)%5;
			count++;
		}
		pthread_mutex_unlock(&m);
		sem_post(&full);
	}
	pthread_exit(0);
}

void * consumer(void * t_num)
{
	int thread_num=*(int *)t_num;
	while(1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&m);
		if(count<=0)
			printf("\nBUFFER EMPTY!!!\n");
		else
		{
			printf("\nCONSUMER %d has consumed: %d\n", thread_num, buffer[out]);
			out=(out+1)%5;
			count--;
		}
		pthread_mutex_unlock(&m);
		sem_post(&empty);
	}
	pthread_exit(0);
}

void main()
{
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, 5);
	pthread_mutex_init(&m, 0);
	pthread_t proth[10], conth[10];
	int i, j, num_pro, num_con;
	printf("\nPlease enter the total number of producers --> ");
	scanf("%d", &num_pro);
	printf("\nPlease enter the total number of consumers --> ");
	scanf("%d", &num_con);
	for(i=0; i<num_pro; i++)
		pthread_create(&proth[i], NULL, producer, &i);
	for(i=0; i<num_con; i++)
		pthread_create(&conth[i], NULL, consumer, &i);
	for(i=0; i<num_pro; i++)
		pthread_join(proth[i], NULL);
	for(i=0; i<num_con; i++)
		pthread_join(conth[i], NULL);
	pthread_mutex_destroy(&m);
	sem_destroy(&full);
	sem_destroy(&empty);
}
