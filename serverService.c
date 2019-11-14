#include <stdio.h>
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
    addToLinkList(username, password, 1);
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
