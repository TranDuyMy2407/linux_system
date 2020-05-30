#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex_var;
void *do_loop2(void *data)
{
	pthread_mutex_lock(&mutex_var);
	for(int i = 0 ; i< 5 ; i++)
	{
		printf("thread 2 is running !!! \n");
		sleep(1);
	}
printf("thread 2 complete !!! \n");
pthread_mutex_unlock(&mutex_var);
pthread_exit(NULL);


}
void *do_loop(void * data)
{
	pthread_mutex_lock(&mutex_var);
	for(int i = 0; i<5 ; i++)
	{
		printf("thread 1 is running  !!! \n");
		sleep(1);
	}
printf("thread 1 complete !!! \n");
pthread_mutex_unlock(&mutex_var);
	pthread_exit(NULL);
}


int main()
{
	int a,b;
	pthread_mutex_init(&mutex_var,NULL);
	pthread_t thread_1,thread_2;
	pthread_create(&thread_2,NULL,  do_loop2, NULL);
	pthread_create(&thread_1,NULL,  do_loop , NULL );
	pthread_join(thread_1,(void *)a);
	pthread_join(thread_2,(void *)b);

	for(int i = 0; i< 5 ; i++)
	{
		printf("main thread is running !!! \n");
		sleep(1);
	}
	return 0;
	
}
