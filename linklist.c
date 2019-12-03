#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linklist.h"
#include "file.h"

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

rank *initRankList(rank *pre, char username[], int win, int lose)
{
  rank *temp, *temp1, *temp2;
  temp = (rank *)malloc(sizeof(rank));
  strcpy(temp->username, username);
  temp->win = win;
  temp->lose = lose;
  if ((win + lose) != 0)
    temp->wlradio = (float)win / (float)(win + lose);
  else
    temp->wlradio = 0;

  if (rankfirst == NULL)
  {
    rankfirst = temp;
    pre = rankfirst;
    temp->next = NULL;
  }
  else
  {
    temp1 = rankfirst;
    while (temp1)
    {
      if (temp->wlradio > temp1->wlradio)
      {
        if (temp1 == rankfirst)
        {
          temp->next = rankfirst;
          rankfirst = temp;
          break;
        }
        else
        {
          temp->next = temp2->next;
          temp2->next = temp;
          break;
        }
      }
      temp2 = temp1;
      if (temp1->next == NULL)
      {
        temp1->next = temp;
        temp->next = NULL;
        break;
      }
      temp1 = temp1->next;
    }
  }
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

void updateWinLose(char WinName[], char LoseName[])
{
  node *account;
  account = getAccount(WinName);
  account->win += 1;

  account = getAccount(LoseName);
  account->lose += 1;
  writeFile();
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

void printfRank()
{
  rank *temp;
  temp = rankfirst;
  while (temp)
  {
    printf("%s %d %d %f\n", temp->username, temp->win, temp->lose, temp->wlradio);
    temp = temp->next;
  }
}
