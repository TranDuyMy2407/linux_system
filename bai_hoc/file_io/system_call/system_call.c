#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

void error(char *a)
{
	printf("%s\n",a);
	exit(1);
}

int main()
{
	char *a = "nguc ban Thao ngon vl !!! \n";
	char buffer[200];
	memset(buffer,0,sizeof(buffer));

	int fd = open("text.txt",O_RDWR);
	if(fd < 0)
		error("cant open the file !! ");

	int fread = read(fd,buffer,sizeof(buffer));
	if(fread < 0)
		error("can not read the file !!! ");
	close(fd);

	 fd = open("text.txt",O_RDWR);
	if(fd < 0)
	 	error("can not open the file !!!");
	
	int fseek = lseek(fd,fread,SEEK_SET);
	int fwrite = write(fd, a , strlen(a));
	if(fwrite < 0)
		error("can not write into the file !!! ");

	close(fd);
	
	printf("fread = %d \n",fread);
	printf("fseek = %d \n",fseek);
	return 0;
	
}
