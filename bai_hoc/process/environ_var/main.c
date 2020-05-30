#include<stdio.h>
#include<stdlib.h>

extern char** environ;

int main(int argc , char** argv)
{
	int i = 0;
	while(environ[i] != NULL)
	{
		printf("%s\n",environ[i]);
		i++;
	}

	for(int j = 0 ; j< argc ; j++)
	{
		printf("tham so thu %d la : %s \n",j,argv[j]);
	}

	return 0;
}
