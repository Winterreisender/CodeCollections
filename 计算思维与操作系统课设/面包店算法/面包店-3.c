#include <stdio.h>

#include <stdbool.h>

#include <unistd.h>

#include <pthread.h>

#include <semaphore.h>



#define THREAD_NUM 30



sem_t active[THREAD_NUM];

sem_t choosing;



int  num[THREAD_NUM] = {0};

int  max_num = 0;



void rand_sleep()

{

	usleep(rand() % 1200);

}





void* runner(void* i_p)

{

	rand_sleep();

	int id = (int) i_p;



	sem_wait(&choosing);

	num[id] = ++max_num;

	sem_post(&choosing);



	printf("thread%d chose num=%d\n", id, num[id]);



	sem_wait(&active[id]);

	// ---------------------

	printf("thread%d run: %d-bread \n", id,id);

	rand_sleep();

	// ---------------------



	num[id] = 0;

    pthread_exit(NULL);



}

void* scheduler(void* none)

{



	for(int k=0;k<10;k++)

	{

		printf("scheduler %d times\n",k);



		printf("thread pool:");

		for(int i=0;i<THREAD_NUM;i++)

		if(num[i]!=0)

			printf("i=%d ",num[i]);

		puts("");



		int min_id[3]={0,1,2};

		int min = 65535;



		for(int i=0; i<THREAD_NUM;i++)

		if(num[i]>0 && num[i] < min)

		{

			min_id[0] = i;

			min = num[i];

		}



		min = 65535;

		for(int i=0; i<THREAD_NUM;i++)

		if( i!=min_id[0] && num[i]>0 && num[i] < min)

		{

			min_id[1] = i;

			min = num[i];

		}



		min = 65535;

		for(int i=0; i<THREAD_NUM;i++)

		if( i!=min_id[0] &&  i!=min_id[1] && num[i]>0 && num[i] < min)

		{

			min_id[2] = i;

			min = num[i];

		}



		if(65535 == min)

			return NULL;



		printf("activating %d,%d,%d\n", min_id[0],min_id[1],min_id[2]);



		sem_post(&active[min_id[0]]);

		sem_post(&active[min_id[1]]);

		sem_post(&active[min_id[2]]);



		while(num[min_id[0]] || num[min_id[1]] || num[min_id[2]]);



		puts("done");



	}

		pthread_exit(NULL);



}

int main()

{



	sem_init(&choosing,0,1);



    pthread_t threads[THREAD_NUM],thread_scheduler;

    for(int i=0;i<THREAD_NUM; i++)



    sem_init(&active[i],0,0); // all disabled

    for(int i=0;i<THREAD_NUM; i++)

        pthread_create(&threads[i],NULL,runner, (void*) i);



    

    pthread_create(&thread_scheduler, NULL, scheduler, NULL);



    for(int i=0;i<THREAD_NUM; i++)



    pthread_join(threads[i],NULL);

        pthread_join(thread_scheduler,NULL);

    pthread_exit(NULL);



    return 0;



}



