#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "linklist.h"

node *first;

FILE *f;
char username[20];
char password[20];
int status, win, lose;
node *s1;

void readFile()
{
  f = fopen("account.txt", "rt");
  if (f == NULL)
  {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    while (1)
    {
      if (fscanf(f, "%s %s %d %d %d", username, password, &status, &win, &lose) == EOF)
        break;
      s1 = initLinkList(s1, username, password, status, win, lose);
    }
    fclose(f);
  }
}

void writeFile()
{
  node *temp = first;
  remove("account.txt");
  f = fopen("account.txt", "w");

  while (temp)
  {
    fprintf(f, "%s %s %d %d %d\n", temp->username, temp->password, temp->status, temp->win, temp->lose);
    temp = temp->next;
  }
  fclose(f);
}
