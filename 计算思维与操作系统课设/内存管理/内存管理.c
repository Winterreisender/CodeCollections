#include <stdio.h>

#include <stdbool.h>

#include <unistd.h>

#include <pthread.h>

#include <semaphore.h>

#include <string.h>



#define THREAD_NUM 3

#define BLOCK_NUM 8





char mem[BLOCK_NUM][8] = {0};

int mem_owner[BLOCK_NUM][8] = {0}; // 0: free ; others : id

char* name0;

char* name1; //xyingming

char* id0; //xuehao



char* alloc_mem(int who, int require_length)

{

	for(int i=0;i<BLOCK_NUM;i++)

	{

		int alloc_able_len = 0;

		int j;

		for(j=0;j<8;j++)

		{

			if(mem_owner[i][j] == 0)

				alloc_able_len++;

			else

				alloc_able_len=0;



			if(alloc_able_len == require_length)

			{

				for(int k=0;k<require_length;k++)

					mem_owner[i][j-k] = who;

				return &mem[i][j-require_length+1];

			}

		}



	}



	return NULL;

}



char* free_mem()

{



}



bool set_mem(int who, char* ptr, char content[8])

{

	//if(who != mem_owner[block_id][0])

	//	return false;



	strcpy(ptr, content);

	return true;

}



void show_mem()

{

	puts("memory data");

	for(int i=0;i<BLOCK_NUM;i++)

	{

		for(int j=0;j<8;j++)

			printf("%2c ", mem[i][j]);

		puts("");

	}



	puts("memory owner");

	for(int i=0;i<BLOCK_NUM;i++)

	{

		for(int j=0;j<8;j++)

			printf("%2d ", mem_owner[i][j]);

		puts("");

	}

}



sem_t active[THREAD_NUM];

sem_t choosing;



int  num[THREAD_NUM] = {65535,65535,65535};

int  max_num = 0;



void rand_sleep()

{

	usleep(rand() % 1200);

}





void* writer(void* i_p)

{

	rand_sleep();

	int id = (int) i_p;



	sem_wait(&choosing);

	num[id] = ++max_num;

	sem_post(&choosing);



	printf("thread%d chose num=%d\n", id, num[id]);



	sem_wait(&active[id]);

	// ---------------------

	id0 = alloc_mem(1,8);

	strcpy(id0, "lovelive");



	name0 = alloc_mem(1,8);

	printf("%p %p\n",name0,mem );

	strcpy(name0, "lovelive");



	name1 = alloc_mem(1,3);

	printf("%p %p\n",name1,mem );

	strcpy(name1, "eng");



	rand_sleep();

	// ---------------------



	num[id] = 0;

    pthread_exit(NULL);

}



void* reader_id(void* i_p)

{

	rand_sleep();

	int id = (int) i_p;



	sem_wait(&choosing);

	num[id] = ++max_num;

	sem_post(&choosing);



	printf("thread%d chose num=%d\n", id, num[id]);



	sem_wait(&active[id]);

	// ---------------------

	for(int i=0;i<8;i++)

	{

		putchar(id0[i]);

	}

	puts("");

	rand_sleep();



	// ---------------------



	num[id] = 0;

    pthread_exit(NULL);

}



void* reader_name(void* i_p)

{

	rand_sleep();

	int id = (int) i_p;



	sem_wait(&choosing);

	num[id] = ++max_num;

	sem_post(&choosing);



	printf("thread%d chose num=%d\n", id, num[id]);



	sem_wait(&active[id]);

	// ---------------------

	for(int i=0;i<8;i++)

	{

		putchar(name0[i]);

	}

	for(int i=0;i<3;i++)

	{

		putchar(name1[i]);

	}

	puts("");

	rand_sleep();

	// ---------------------



	num[id] = 0;

    pthread_exit(NULL);

}





void* scheduler(void* none)

{



	for(int k=0;k<3;k++)

	{

		sleep(1);

		printf("scheduler %d times\n",k);



		printf("thread pool:");

		for(int i=0;i<THREAD_NUM;i++)

		if(num[i]!=0)

			printf("%d=%d ",i,num[i]);

		puts("");



		int min_id[1]={0};

		int min = 65535;



		for(int i=0; i<THREAD_NUM;i++)

		if(num[i]>0 && num[i] < min)

		{

			min_id[0] = i;

			min = num[i];

		}



		if(65535 == min)

			return NULL;



		printf("activating %d\n", min_id[0]);



		sem_post(&active[min_id[0]]);



		while(num[min_id[0]]);



		puts("done");



	}

		pthread_exit(NULL);



}





int main()

{



	alloc_mem(2,4);

	alloc_mem(3,7);

	alloc_mem(4,2);



	show_mem();





	sem_init(&choosing,0,1);



    pthread_t threads[THREAD_NUM],thread_scheduler;

    for(int i=0;i<THREAD_NUM; i++)



    sem_init(&active[i],0,0); // all disabled

    

    pthread_create(&threads[0],NULL,writer, 0);

    pthread_create(&threads[1],NULL,reader_name, (void*) 1);

    pthread_create(&threads[2],NULL,reader_id, (void*) 2);



    

    pthread_create(&thread_scheduler, NULL, scheduler, NULL);



    for(int i=0;i<THREAD_NUM; i++)

    	pthread_join(threads[i],NULL);

    

    pthread_join(thread_scheduler,NULL);

    show_mem();

    pthread_exit(NULL);



    return 0;



}



