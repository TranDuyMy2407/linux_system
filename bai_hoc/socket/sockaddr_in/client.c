#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<signal.h>
#include<stdlib.h>
#include<pthread.h>

int sockfd;

void error(char msg[])
{
	printf("%s\n",msg);
	exit(1);
}

void Send_data()
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
char receive_buffer[1000];
	while(1)
	{
		memset(receive_buffer,0,sizeof(receive_buffer));
		int fread = recv(sockfd,receive_buffer,sizeof(receive_buffer),0);
		if(fread > 0)
			printf("server>%s \n",receive_buffer);

		else if(fread == 0)
			break;

		else{}
}
}

void catch_signal(int signal)
{
	close(sockfd);
	printf("freed file descriptor !!! \n");
	exit(0);	

}

int main()
{
	signal(SIGINT,catch_signal);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("cant create the socket !!! ");

	struct sockaddr_in client_info, server_info;
	socklen_t server_addrlen = sizeof(server_info);
	socklen_t client_addrlen = sizeof(client_info);
	
	memset(&server_info , 0, server_addrlen);
	memset(&client_info, 0 , client_addrlen);

	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = inet_addr("192.168.1.105");
	server_info.sin_port = htons(3333);

	int err = connect(sockfd , (struct sockaddr*)&server_info, client_addrlen);

	if(err < 0)
		error("connecting error !!! ");

	getsockname(sockfd,(struct sockaddr*)&client_info,&client_addrlen);
	getpeername(sockfd,(struct sockaddr*)&server_info, &server_addrlen);
	

	printf("Connect to server :  %s:%d\n",inet_ntoa(server_info.sin_addr),ntohs(server_info.sin_port));
	printf("You are : %s:%d \n ", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

	pthread_t send_msg , receive_msg;
	pthread_create(&send_msg,NULL,(void*)Send_data,NULL);
	pthread_create(&receive_msg,NULL,(void*)Receive_data,NULL);
	

		
	while(1);	
}


