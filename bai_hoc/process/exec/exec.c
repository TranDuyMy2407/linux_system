#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("test exect !! \n");
	execlp("ls","ls", "-l",0);
	printf("hello wolrd !!! \n");
	return 0;
}
