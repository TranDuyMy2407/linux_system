#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include "sock_define.h"

void error(char *msg)
{
	printf("%s",msg);
	exit(1);
}

void Init(struct List *l)
{
        l->phead = NULL;
}

void del_enter(char *msg,int n)
{
	for(int i = 0  ;i<n ; i++)
	{
		if(msg[i] == '\n')
		{
			msg[i] = '\0';
			break;	
		}
	}
}

struct Node *NewNode(int fd , char *ip, struct List *l)
{
	struct Node *p = (struct Node*)malloc(sizeof(struct Node));
	
	p->fd = fd;
	memset(p->ip,0,IP_LEN);
	strcpy(p->ip,ip);
	p->next = NULL;
	p->prev = NULL;

	
	if(l->phead == NULL)	
		l->phead = p;

	else
	{
		struct Node *temp = l->phead;
		while(temp->next != NULL)
			temp = temp->next;

		temp->next = p;
		p->prev = temp;
	}

	return p;
}





void send_all_clients(struct Node *p, char *msg, struct List *l)
{
        struct Node *temp = l->phead;
        while(temp != NULL)
        {
                if(temp->fd != p->fd)
                {
                        send(temp->fd,msg,MSG_LEN,0);
                }
         
                temp=temp->next;
        }
}


