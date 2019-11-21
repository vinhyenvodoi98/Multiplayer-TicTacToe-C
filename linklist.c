#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linklist.h"

node *initLinkList(node *pre, char username[], char password[], int status, int win, int lose)
{
  node *temp;
  temp = (node *)malloc(sizeof(node));
  strcpy(temp->username, username);
  strcpy(temp->password, password);
  temp->loginTimeLeft = 3;
  temp->status = status;
  temp->win = win;
  temp->lose = lose;
  temp->next = NULL;
  temp->isLogin = 0;

  if (first == NULL)
  {
    first = temp;
    pre = first;
  }
  else
  {
    pre->next = temp;
    pre = pre->next;
  }
  return pre;
}

node *getAccount(char username[])
{
  node *account;
  account = first;

  while (account)
  {
    if (strcmp(account->username, username) == 0)
    {
      break;
    }
    account = account->next;
  }
  return account;
}

void addToLinkList(char username[], char password[], int status, int win, int lose)
{
  node *checkLast = first;
  node *temp;
  temp = (node *)malloc(sizeof(node));

  strcpy(temp->username, username);
  strcpy(temp->password, password);
  temp->status = status;
  temp->win = win;
  temp->lose = lose;
  temp->loginTimeLeft = 3;
  temp->isLogin = 0;
  temp->next = NULL;
  while (checkLast->next != NULL)
  {
    checkLast = checkLast->next;
  }

  checkLast->next = temp;
}

int checkAccountExist(char username[])
{
  int isExist = 0;
  node *temp;
  temp = first;
  while (temp)
  {
    if (strcmp(temp->username, username) == 0)
    {
      isExist = 1;
      break;
    }
    temp = temp->next;
  }

  return isExist;
}

int checkPassword(char username[], char password[])
{
  int isCorrect = 0;
  node *temp;
  temp = first;

  while (temp)
  {
    if (strcmp(temp->username, username) == 0)
    {
      if (strcmp(temp->password, password) == 0)
      {
        isCorrect = 1;
        break;
      }
    }
    temp = temp->next;
  }
  return isCorrect;
}

void printfAllUser()
{
  node *temp;
  temp = first;
  while (temp)
  {
    printf("%s %s %d %d %d\n", temp->username, temp->password, temp->status, temp->win, temp->lose);
    temp = temp->next;
  }
}
