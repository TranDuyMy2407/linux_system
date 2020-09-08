#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>
#include"../inc/sock_define.h"

int server_fd;
List *l;

void clean()
{
	while(l->phead != NULL)
	{
		close(l->phead->fd);
		  Node *temp = l->phead;
		l->phead = l->phead->next;
		free(temp);
	}

	close(server_fd);
	printf("Done !!! \n");
	exit(0);
}


void client_handler(  Node* p)
{
	
	char nickname[NAME_LEN];
	char send_data[MSG_LEN];
	char receive_data[MSG_LEN];



          Node *temp = l->phead;

	while(1)
	{	
		char flag = '0';
		memset(nickname,0,NAME_LEN);
		recv(p->fd,nickname,NAME_LEN,0);
		for(temp = l->phead; temp != NULL ;temp =temp->next)
		{
			if(strcmp(temp->name,nickname)==0)
				flag = '1';
		}

		send(p->fd,&flag,1,0);
		if(flag == '0')
			break;
	}


	memset(p->name,0,NAME_LEN);
	strcpy(p->name,nickname);

	printf("%s has joined the room !!! \n",p->name);
	sprintf(send_data,"%s has joined the room !!!\n",p->name);
	send_all_clients(p,send_data,l);


	int leave = 0;
	
	while(leave == 0)
	{
		memset(send_data,0,MSG_LEN);
		memset(receive_data,0,MSG_LEN);

		int ret = recv(p->fd, receive_data , MSG_LEN ,0);
		
		if(ret > 0)
		{
			printf("%s>%s",p->name,receive_data);
			sprintf(send_data,"%s>%s",nickname,receive_data);
		}

		
		else if(ret == 0)
		{
			printf("%s has left the room  !!!\n",p->name);
			sprintf(send_data,"%s has left the room !!! \n",p->name);
			leave = 1;
		}

		else
		{
			printf("cant read the file !!! \n");
			leave = 1;
		}

		send_all_clients(p,send_data,l);				

	}

	if(p == l->phead)
	{
		if(p->next == NULL)
		{
			l->phead = NULL;
			free(p);
		}	
		

	
		else
		{
			l->phead = p->next;
			p->next->prev = NULL;
			free(p);
		}
	}


	else if(p->next == NULL)
	{
		p->prev->next = NULL;
		free(p);
	}


	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);
	}
	

}

int main()
{

	//allocate memory for the list

	//set up signal function

	l = (List*)(malloc(sizeof(List)));
	l->phead = NULL;
	signal(SIGINT,clean);

	//sockaddr_in  ure variables to store server and clients information
	struct sockaddr_in server_info,client_info;
	socklen_t s_addrlen = sizeof(server_info);	
	socklen_t c_addrlen = sizeof(client_info);

	//write NULL character to all components of  ure variable
	memset(&server_info,0,s_addrlen);
	memset(&client_info,0,c_addrlen);
	

	server_info.sin_family = AF_INET;

	//use loopback address
	server_info.sin_addr.s_addr = inet_addr("127.0.0.1");

	//use 3333 port number
	server_info.sin_port = htons(3333);

	/*
	 *socket : create a socket
	 *AF_INET: format address for host and port number
	 * 0 : use TCP/IP protocol (1 for UDP)
	 * */
	server_fd = socket(AF_INET, SOCK_STREAM,0);


	//assign a address to server socket
	bind(server_fd,(struct sockaddr*)&server_info,s_addrlen);

	//specifies maximum number of connections that can be pending
	listen(server_fd,5);

	printf("SERVER IP: %s \n",inet_ntoa(server_info.sin_addr));
	printf("PORT: %d \n",ntohs(server_info.sin_port));


	while(1)
	{
		//waiting for clients request
		int client_fd = accept(server_fd,(struct sockaddr*)&client_info,&c_addrlen);

		//create a node to store information of client
		  Node *p = NewNode(client_fd,inet_ntoa(client_info.sin_addr),l);

		//create a new thread to handler the requets
		pthread_t a = pthread_create(&a,NULL,(void*)client_handler,p);

	}

}

