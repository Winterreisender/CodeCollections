#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



#define PHD_NUM 5

#define CHOP_NUM 5



sem_t sems[CHOP_NUM];



void *runner(void *id_p)

{

	int id = (int) id_p;

	int left = id;

	int right = (id+1)%CHOP_NUM; 



	printf("PhD %d Waiting left chop %d...\n", id,left);

	sem_wait(&sems[left]);

	sleep(2);

	printf("PhD %d got left chop %d , waiting right chop %d...\n", id,left,right);

	sem_wait(&sems[right]);



	printf("PhD %d got %d,%d Eating...\n", id, left,right);

	sleep(2);

	printf("PhD %d Done\n", id);



	sem_post(&sems[left]);

	sem_post(&sems[right]);



	pthread_exit(NULL);

}



int main(int argc, char *argv[])

{

	pthread_t threads[PHD_NUM];



	for(int i = 0; i< CHOP_NUM; i++)

		sem_init(&sems[i],0,1);



	for(int i=0;i<PHD_NUM;i++)

	{

		

		int rc = pthread_create(&threads[i], NULL, runner, (void *)i);

		if (rc){

			printf("ERROR; return code from pthread_create() is %d\n", rc);

			exit(-1);

		}

	}



	

	for(int i=0;i<PHD_NUM;i++)

		pthread_join(threads[i],NULL);



	pthread_exit(NULL);  

}

