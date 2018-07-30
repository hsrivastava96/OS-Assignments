#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex, wrt;
int readcount=0;

void * reader(void * data)
{
	sem_wait(&mutex);
	readcount++;
	if(readcount==1)
		sem_wait(&wrt);
	sem_post(&mutex);
	printf("\nReading...\n");
	sem_wait(&mutex);
	readcount--;
	if(readcount==0)
		sem_post(&wrt);
	sem_post(&mutex);
}

void * writer(void * data)
{
	sem_wait(&wrt);
	printf("\nWriting...\n");
	sem_post(&wrt);
}

int main()
{
	sem_init(&wrt, 0, 1);
	sem_init(&mutex, 0, 1);
	pthread_t read[10], write[10];
	int i=0;
	for(i=0; i<10; i++)
	{
		pthread_create(&write[i], NULL, writer, NULL);
		pthread_create(&read[i], NULL, reader, NULL);
	}
	for(i=0; i<10; i++)	
		pthread_join(write[i], NULL);
	for(i=0; i<10; i++)		
		pthread_join(read[i], NULL);
	sem_destroy(&mutex);
	sem_destroy(&wrt);
	return 0;
}
