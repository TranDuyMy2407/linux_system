#define MSG_LEN	   200
#define NAME_LEN   100
#define IP_LEN	   16




struct Node
{
	int fd;
	char name[NAME_LEN];
	char ip[IP_LEN];
	struct Node *next;
	struct Node *prev;
};

struct List
{
	struct Node *phead;
};


void Init(struct List *l);
void error(char *msg);
void del_enter(char *msg , int n);
struct Node *NewNode(int fd , char *ip, struct List *l);
void send_all_clients(struct Node *p, char *msg , struct List *l);



