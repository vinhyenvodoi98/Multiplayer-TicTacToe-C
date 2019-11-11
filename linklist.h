#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef struct node
{
  char username[20];
  char password[20];
  int status;
  int loginTimeLeft;
  int isLogin;
  struct node *next;
} node;

node *first;
node *account;
int islogin;

node *initLinkList();
node *getAccount(char username[]);
void addToLinkList(char username[], char password[], int status);
void printfAllUser();
int checkPassword(char username[], char password[]);
int checkAccountExist(char username[]);

#endif
