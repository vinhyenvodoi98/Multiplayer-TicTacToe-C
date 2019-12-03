#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef struct node
{
  char username[20];
  char password[20];
  int status;
  int win;
  int lose;
  int loginTimeLeft;
  int isLogin;
  struct node *next;
} node;

typedef struct rank
{
  char username[20];
  int win;
  int lose;
  float wlradio;
  struct rank *next;
} rank;

rank *rankfirst;

node *first;
node *account;
int islogin;

rank *initRankList();
node *initLinkList();
node *getAccount(char username[]);
void addToLinkList(char username[], char password[], int status, int win, int lose);
void printfAllUser();
int checkPassword(char username[], char password[]);
int checkAccountExist(char username[]);
void updateWinLose();
void printfRank();

#endif
