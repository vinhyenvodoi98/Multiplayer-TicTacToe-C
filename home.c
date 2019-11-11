#include <stdio.h>
#include <string.h>
#include "file.h"

char *_signin(char username[20], char password[20])
{
  if (account == NULL)
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
          return ("Login successfully ");
        }
        else
        {
          account->loginTimeLeft--;
          // return ("Password is incorrect you only have %d time left to login \n", account->loginTimeLeft);
          return ("Password is incorrect you only have 3 time left to login \n");
          if (account->loginTimeLeft == 0)
          {
            return (" Account is blocked ! \n");
            account->status = 0;
            writeFile();
          }
        }
      }
      else
      {
        return (" Account is blocked ! \n");
      }
    }
    else
    {
      return ("Cannot find account \n");
    }
  }
  else
  {
    return ("You are already login \n");
  }
}

char *_signout(char username[20])
{
  if (account == NULL)
  {
    return ("Account is not sign in\n");
  }
  else
  {
    if (checkAccountExist(username) == 1)
    {
      if (strcmp(account->username, username) == 0)
      {
        account = NULL;
        return ("Goodbye");
      }
      else
      {
        return ("This is not your username\n");
      }
    }
    else
    {
      return ("Cannot find account \n");
    }
  }
}
