#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int child_status;
	if( fork() == 0 )
	{
		printf("pid of child process : %d \n",getpid());
		for(int i = 0 ;i<5 ; i++)
		{
			printf("this is child process !!! \n");
			sleep(1);	
		}
	}

	else
	{
		printf("parent process is waiting child process !!\n");
		printf("pid of parent process : %d \n", getpid());
		wait(&child_status);
		for(int i = 0;i<5;i++)
		{
			printf("this is parent process !!! \n");
			sleep(1);
		}
		printf("child process status : %d",child_status);	
	}
	

	return 0;
}
