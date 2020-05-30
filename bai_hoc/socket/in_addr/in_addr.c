#include<stdio.h>
#include <stdlib.h>
#include <netinet/in.h> //for struct in_addr
#include <arpa/inet.h>  //for inet_ntoa()


int main(){

	struct in_addr a;
	
	char *ip = (char *)(&a.s_addr);
	*ip = 10;
	*(ip + 1) = 0;
	*(ip + 2) = 0;
	*(ip + 3) = 1;
	
	printf("ip : %s \n",inet_ntoa(a));
 



}
