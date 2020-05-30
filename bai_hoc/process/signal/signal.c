#include<stdio.h>
#include<signal.h>
void catch_signal(int signal)
{
	printf("signal have been called !!! \n");
}

int main()
{
	signal(SIGINT,catch_signal);
	while(1)
	{
		printf("pid of process : %d  !!! \n",getpid());
		sleep(1);
	}
return 0;
}
