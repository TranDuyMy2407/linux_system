#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<signal.h>
#include<pthread.h>



int server_fd,sockfd;

void error(char *message)
{
	printf("%s \n",message);
	exit(1);
}

void  Send_data()

{
	char send_buffer[1000] = {};
	while(1)
	{
		memset(send_buffer,0,sizeof(send_buffer));

		fgets(send_buffer,sizeof(send_buffer),stdin);
		if(strlen(send_buffer) > 0)
			 send(sockfd,send_buffer,sizeof(send_buffer),0);


		else
			break;
		
	}
}


void Receive_data()
{
	char receive_buffer[1000] = {};
	
	while(1)
	{
		memset(receive_buffer,0,sizeof(receive_buffer))	;	
		int fread = recv(sockfd,receive_buffer,sizeof(receive_buffer),0);
		if(fread > 0)
				printf("Client>%s \n",receive_buffer)	;

		else if (fread == 0)
			break;

		else{}
	}
}
void catch_signal(int signal)
{
	close(server_fd);
	printf("freed file descriptor  !!!\n ");
	exit(0);
}


int main()
{
	signal(SIGINT,catch_signal);
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0)	
		error("cant  create socket !!! ");

	
	struct sockaddr_in server_info , client_info;
	int server_addrlen = sizeof(server_info);
	int client_addrlen = sizeof(client_info);

	memset(&server_info,0,server_addrlen);
	memset(&client_info,0,client_addrlen);

	server_info.sin_family =AF_INET;
	server_info.sin_addr.s_addr = inet_addr("192.168.1.105");
	server_info.sin_port = htons(3333);

	bind(server_fd , (struct sockaddr *)&server_info , server_addrlen);
	listen(server_fd, 5);


	getsockname(server_fd,(struct sockaddr *)&server_info,(socklen_t*)&server_addrlen);

	printf("\nstart server on  %s:%d\n",inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
	
	
	while(1)
	{
		
	 	 sockfd = accept(server_fd,(struct sockaddr*)&client_info,(socklen_t*)&client_addrlen);
		pthread_t send,receive;
		pthread_create(&send,NULL,(void*)Send_data,NULL);
		pthread_create(&receive,NULL,(void*)Receive_data,NULL);
	}
}
