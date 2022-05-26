#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


sem_t lock;

char* share_res;

void *writer(void *none)
{

	sem_wait(&lock);
		puts("Entering Cirtical Zone");

		puts("writing share_res:");
		strcpy(share_res,"Hello World!");

		puts("Entering Cirtical Zone");
	sem_post(&lock); // Exit lock


	pthread_exit(NULL);
}
void *reader(void *none)
{

	sem_wait(&lock); // Lock
		puts("Entering Cirtical Zone");

		puts("reading share_res:");
		puts(share_res);

		puts("Entering Cirtical Zone");
	sem_post(&lock); // Exit lock


	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

	share_res = malloc(1024);
	sem_init(&lock,0,1);

	pthread_t thread_rd, thread_wt;
	pthread_create(&thread_wt, NULL, writer, NULL);
	pthread_create(&thread_rd, NULL, reader, NULL);

	
	pthread_join(thread_wt,NULL);
	pthread_join(thread_rd,NULL);
	pthread_exit(NULL);  
}