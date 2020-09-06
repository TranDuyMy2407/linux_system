#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"../inc/sock_define.h"


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
		fgets(send_buffer,MSG_LEN,stdin);
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
			printf("\r%s",receive_buffer);

		else if(ret == 0)
		{
			printf("the server has closed");
			catch_signal();
		}




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
	server_info.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_info.sin_port = htons(3333);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("cant create the file !!! \n");


	//connect to server
	int err = connect(sockfd,(struct sockaddr*)&server_info,c_addrlen);
	if(err < 0)
		error("connecting error !!! \n");


	getsockname(sockfd,(struct sockaddr*)&client_info, &c_addrlen);
	printf("IP: %s \n", inet_ntoa(client_info.sin_addr));
	printf("CONNECTING TO SERVER: %s:%d \n", inet_ntoa(server_info.sin_addr),ntohs(server_info.sin_port));


		
		char flag;
		
		//enter nickname
		while(1)
		{
			char nickname[NAME_LEN];
			do
			{
		
				memset(nickname,0,NAME_LEN);
				printf("enter your nickname: ");
				fgets(nickname,NAME_LEN,stdin);
				for(int i=0;i<strlen(nickname);i++)
				{
					if(nickname[i]=='\n')
					{
						nickname[i]='\0';
						break;
					}
				}	

				if(strlen(nickname) < 2 || strlen(nickname) > NAME_LEN)
					printf("the nickname is invalid , please try again !!! \n");	
		
	
			}while(strlen(nickname) < 2 || strlen(nickname) > NAME_LEN);
	
			//send flag to server 
			send(sockfd,nickname,strlen(nickname),0);

			//receive flag from server to verify the name is valid
			recv(sockfd,&flag,1,0);

			if(flag == '0')
				break;

		}


		

	


		
	pthread_t send_t;
	

	//create thread to send data
	if(pthread_create(&send_t, NULL, (void *)send_data, NULL) < 0)
		error("thread creation error !!! \n");


	//create thread to receive data
	pthread_t recv_t;
	if(pthread_create(&recv_t,NULL, (void *)receive_data,NULL) < 0)
		error("thread creation error !!! \n");
	
	

	while(1);
	
}

