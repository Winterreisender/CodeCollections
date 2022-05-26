#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include <semaphore.h>



#define READER_NUM 3

#define WRITER_NUM 3



#define MAX_USLEEP 65535



sem_t write_lock; //in wt 写者在写入数据文件时对共享数据文件具有独占访问权

sem_t not_reading[READER_NUM]; //between rd and wr

sem_t not_writing[WRITER_NUM]; //between rd and wr



int article = 0;



void *writer(void *id_p)

{

	int id = (int) id_p;

	for(int i=0;i<20;i++){

		usleep( rand()%MAX_USLEEP ); // simulate any time



		printf("Writer %d waiting not_writing[%d] \n", id,id);

		sem_wait(&not_writing[id]);



		printf("Writer %d waiting all reader's not_reading \n", id);

		for (int i=0; i<READER_NUM; i++)

			sem_wait(&not_reading[i]);



		printf("Writer %d waiting write_lock \n", id);

		sem_wait(&write_lock);

		puts("Entering Cirtical Zone");



			int new_article = rand();

			printf("Writer %d wrote article: %d \n", id ,new_article);

			article = new_article;

			usleep( rand()%MAX_USLEEP );



		puts("Exited Cirtical Zone");

		sem_post(&write_lock); // Exit writing

		sem_post(&not_writing[id]);

		for (int i=0; i<READER_NUM; i++)

			sem_post(&not_reading[i]);

	}

	pthread_exit(NULL);

}



void *reader(void *id_p)

{

	for(int i=0;i<20;i++){

		int id = (int) id_p;

		usleep( rand()%MAX_USLEEP );



		printf("Reader %d waiting not_reading[%d] \n",id, id);

		sem_wait(&not_reading[id]);



		printf("Reader %d reading article: %d \n",id, article);

		usleep( rand()%MAX_USLEEP );

		printf("Reader %d finished reading article: %d \n",id, article);



		sem_post(&not_reading[id]);

	}

	pthread_exit(NULL);

}



int main(int argc, char *argv[])

{

	srand(125);



	sem_init(&write_lock,0,1);



	for(int i=0;i<READER_NUM;i++)

		sem_init(&not_reading[i],0,1);

	for(int i=0;i<WRITER_NUM;i++)

		sem_init(&not_writing[i],0,1);





	pthread_t thread_rd[READER_NUM], thread_wt[WRITER_NUM];



	for (int i=0;i<READER_NUM;i++)

		pthread_create(&thread_rd[i], NULL, reader, (void*)i);



	for (int i=0;i<WRITER_NUM;i++)

		pthread_create(&thread_wt[i], NULL, writer, (void*)i);



	for (int i=0;i<READER_NUM;i++)

		pthread_join(thread_rd[i], NULL);



	for (int i=0;i<WRITER_NUM;i++)

		pthread_join(thread_wt[i], NULL);



	pthread_exit(NULL);  

}