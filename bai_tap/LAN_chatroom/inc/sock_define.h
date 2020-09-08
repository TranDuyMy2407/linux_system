#define MSG_LEN	   1000
#define NAME_LEN   1000
#define IP_LEN	   16



typedef struct Node
{
	int fd;
	char name[NAME_LEN];
	char ip[IP_LEN];
	struct Node *next;
	struct Node *prev;
}Node;

typedef struct List
{
	struct Node *phead;
}List;


void error(char *msg);
struct Node *NewNode(int fd , char *ip, struct List *l);
void send_all_clients(struct Node *p, char *msg , struct List *l);



