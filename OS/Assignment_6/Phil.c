#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num+4)%N
#define RIGHT (ph_num+1)%N

sem_t mutex, phil_signal[N];

int state[N], phil[N]={0, 1, 2, 3, 4};

void test(int ph_num)
{
	if(state[ph_num]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
	{
		state[ph_num]=EATING;
		sleep(2);
		printf("\nPhilosopher %d is eating\n", ph_num+1);
		sem_post(&phil_signal[ph_num]);
	}
}

void put_fork(int ph_num)
{
	sem_wait(&mutex);
	state[ph_num]=THINKING;
	printf("\nPhilosopher %d has put the forks down.\n", ph_num+1);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);	
}

void take_fork(int ph_num)
{
	sem_wait(&mutex);
	state[ph_num]=HUNGRY;
	printf("\nPhilosopher %d is Hungry\n", ph_num+1);
	test(ph_num);
	sem_post(&mutex);
	sem_wait(&phil_signal[ph_num]);
	sleep(1);
}

void * phils(void * pnum)
{
	while(1)
	{
		int *ph_num=pnum;
		sleep(1);
		take_fork(*ph_num);
		sleep(0);
		put_fork(*ph_num);
	}
}

int main()
{
	sem_init(&mutex, 0, 1);
	int i=0;
	pthread_t phil_tid[N];
	for(i=0; i<N; i++)
		sem_init(&phil_signal[i], 0, 0);
	for(i=0; i<N; i++)
		pthread_create(&phil_tid[i], NULL, phils, &phil[i]);
	for(i=0; i<N; i++)
		pthread_join(phil_tid[i], NULL);
	sem_destroy(&mutex);
	for(i=0; i<N; i++)
		sem_destroy(&phil_signal[i]);
	return 0;
}
