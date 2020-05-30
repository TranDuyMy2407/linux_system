#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"sock_define.h"


int sockfd;

void catch_signal()
{
	printf("Byeee!!!\n");
	close(sockfd);
	exit(0);
}


void send_data()
{
	char send_buffer[MSG_LEN];

	while(1)
	{
		memset(send_buffer,0,MSG_LEN);
		fgets(send_buffer,MSG_LEN, stdin);
		if(strlen(send_buffer) > 0)
			send(sockfd,send_buffer,MSG_LEN,0);
	}

	
}

void receive_data()
{

	char receive_buffer[MSG_LEN];
	int ret;
	while(1)
	{
		memset(receive_buffer,0,MSG_LEN);
		ret = recv(sockfd,receive_buffer,MSG_LEN,0);
		if(ret > 0)
		{
			del_enter(receive_buffer,strlen(receive_buffer));
			printf("%s\n",receive_buffer);
		}

		else if(ret == 0)
		{
			printf("the server has closed");
			catch_signal();
		}


		else{}
	}
	
}


int main()
{

	signal(SIGINT, catch_signal);
	struct sockaddr_in server_info,client_info;
	socklen_t s_addrlen = sizeof(server_info);
	socklen_t c_addrlen = sizeof(client_info);

	memset(&server_info,0,s_addrlen);
	memset(&client_info,0,c_addrlen);

	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = inet_addr("192.168.1.105");
	server_info.sin_port = htons(3333);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("cant create the file !!! \n");

	int err = connect(sockfd,(struct sockaddr*)&server_info,c_addrlen);
	if(err < 0)
		error("connecting error !!! \n");


	getsockname(sockfd,(struct sockaddr*)&client_info, &c_addrlen);
	printf("IP: %s \n", inet_ntoa(client_info.sin_addr));
	printf("CONNECTING TO SERVER: %s:%d \n", inet_ntoa(server_info.sin_addr),ntohs(server_info.sin_port));

	
	char nickname[NAME_LEN];
	
	do
	{
		
		memset(nickname,0,NAME_LEN);
		printf("enter your nickname: ");
		fgets(nickname,NAME_LEN,stdin);

		if(strlen(nickname) < 2 || strlen(nickname) > NAME_LEN)
			printf("the nickname is invalid , please try again !!! \n");	
	
	
	}while(strlen(nickname) < 2 || strlen(nickname) > NAME_LEN);
	
	del_enter(nickname,strlen(nickname));
	send(sockfd,nickname,strlen(nickname),0);

		
	pthread_t send_t;
	
	if(pthread_create(&send_t, NULL, (void *)send_data, NULL) < 0)
		error("thread creation error !!! \n");

	pthread_t recv_t;
	if(pthread_create(&recv_t,NULL, (void *)receive_data,NULL) < 0)
		error("thread creation error !!! \n");
	
	

	while(1);
	
}

