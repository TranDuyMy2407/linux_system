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
struct List *l;

void clean()
{
	while(l->phead != NULL)
	{
		close(l->phead->fd);
		struct Node *temp = l->phead;
		l->phead = l->phead->next;
		free(temp);
	}

	close(server_fd);
	printf("Done !!! \n");
	exit(0);
}


void client_handler(struct Node *p)
{
	
	char nickname[NAME_LEN];
	char send_data[MSG_LEN];
	char receive_data[200];



        struct Node *temp = l->phead;

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
			printf("%s>%s\n",p->name,receive_data);
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
			return;
		}	
		

	
		else
		{
			l->phead = p->next;
			p->next->prev = NULL;
			free(p);
			return;
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

	printf("hello \n");
	l = (struct List *)malloc(sizeof(struct List));
	l->phead = NULL;

	signal(SIGINT,clean);
	printf("hello \n");
	struct sockaddr_in server_info,client_info;
	socklen_t s_addrlen = sizeof(server_info);	
	socklen_t c_addrlen = sizeof(client_info);

	memset(&server_info,0,s_addrlen);
	memset(&client_info,0,c_addrlen);
	
	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_info.sin_port = htons(3333);
	server_fd = socket(AF_INET, SOCK_STREAM,0);
	bind(server_fd,(struct sockaddr*)&server_info,s_addrlen);
	listen(server_fd,5);

	printf("SERVER IP: %s \n",inet_ntoa(server_info.sin_addr));
	printf("PORT: %d \n",ntohs(server_info.sin_port));


	while(1)
	{
		int client_fd = accept(server_fd,(struct sockaddr*)&client_info,&c_addrlen);
		struct Node *p = NewNode(client_fd,inet_ntoa(client_info.sin_addr),l);

		pthread_t a;
		pthread_create(&a,NULL,(void*)client_handler,p);

	}

}

