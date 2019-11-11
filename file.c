#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "linklist.h"

node *first;

FILE *f;
char username[20];
char password[20];
int status;
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
      if (fscanf(f, "%s %s %d", username, password, &status) == EOF)
        break;
      s1 = initLinkList(s1, username, password, status);
    }
    fclose(f);
  }
}

void writeFile()
{
  node *temp = first;
  f = fopen("account.txt", "w");

  while (temp)
  {
    fprintf(f, "%s %s %d\n", temp->username, temp->password, temp->status);
    temp = temp->next;
  }
  fclose(f);
}