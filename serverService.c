#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

char *_signin(char username[20], char password[20])
{
  if (checkAccountExist(username) == 1)
  {
    account = getAccount(username);
    if (account->status == 1)
    {
      if (checkPassword(username, password))
      {
        account->isLogin = 1;
        account->loginTimeLeft = 3;
        return ("Login successfully");
      }
      else
      {
        return ("Password is incorrect");
      }
    }
    else
    {
      return ("Account is blocked");
    }
  }
  else
  {
    return ("Cannot find account");
  }
}

char *_signup(char username[20], char password[20])
{
  if (checkAccountExist(username) == 1)
  {
    return ("Username is already exits");
  }
  else
  {
    addToLinkList(username, password, 1, 0, 0);
    account = getAccount(username);
    account->isLogin = 1;
    account->loginTimeLeft = 3;
    writeFile();
    return ("Signup successfully");
  }
}

char *_signout(char username[20])
{
  if (checkAccountExist(username))
  {
    if (!strcmp(account->username, username))
    {
      account = NULL;
      return ("Goodbye");
    }
    else
    {
      return ("This is not your username");
    }
  }
  else
  {
    return ("Cannot find account");
  }
}

char *_lockAccount(char username[20])
{
  account = getAccount(username);
  account->status = 0;
  writeFile();
  return ("Account is blocked");
}

char *_getRank(char name[])
{
  rank *s1, *ranktemp;
  node *temp;
  char *sendRank = (char *)calloc(500, sizeof(char));
  char *str;
  int i = 1;

  temp = first;
  while (temp)
  {
    s1 = initRankList(s1, temp->username, temp->win, temp->lose);
    temp = temp->next;
  }

  ranktemp = rankfirst;

  while (ranktemp)
  {

    str = (char *)calloc(3, sizeof(char));
    if (strcmp(name, ranktemp->username) == 0)
      strcat(sendRank, "\033[1;33m");

    sprintf(str, "%d", i);
    strcat(sendRank, str);
    strcat(sendRank, "\t");
    strcat(sendRank, ranktemp->username);
    strcat(sendRank, "\t");
    str = (char *)calloc(3, sizeof(char));
    sprintf(str, "%d", ranktemp->win);
    strcat(sendRank, str);
    strcat(sendRank, "\t");
    str = (char *)calloc(3, sizeof(char));
    sprintf(str, "%d", ranktemp->lose);
    strcat(sendRank, str);
    strcat(sendRank, "\t");
    str = (char *)calloc(10, sizeof(char));
    gcvt(ranktemp->wlradio, 10, str);
    strcat(sendRank, str);

    if (strcmp(name, ranktemp->username) == 0)
      strcat(sendRank, "\033[0m");

    strcat(sendRank, "\n");
    i++;
    ranktemp = ranktemp->next;
  }
  rankfirst = NULL;

  return sendRank;
}