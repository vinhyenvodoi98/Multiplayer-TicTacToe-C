#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>  // for open
#include <unistd.h> // for close
#include <sys/types.h>
#include "clientP2P.h"

#define MAX 80
#define SA struct sockaddr

void checkHostName(int hostname)
{
  if (hostname == -1)
  {
    perror("gethostname");
    exit(1);
  }
}

// Returns host information corresponding to host name
void checkHostEntry(struct hostent *hostentry)
{
  if (hostentry == NULL)
  {
    perror("gethostbyname");
    exit(1);
  }
}

// Converts space-delimited IPv4 addresses
// to dotted-decimal format
void checkIPbuffer(char *IPbuffer)
{
  if (NULL == IPbuffer)
  {
    perror("inet_ntoa");
    exit(1);
  }
}

// --------------------------------------------------------

char *genPort()
{
  struct sockaddr_in servaddr;
  struct hostent *host_entry;
  int sockfd;
  char port[8];

  char hostbuffer[256];
  char *IPbuffer, *Port = (char *)calloc(20, sizeof(char));
  int hostname;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    printf("socket creation failed...\n");
    exit(0);
  }
  else
    printf("Create ip\n");

  bzero(&servaddr, sizeof(servaddr));
  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = 0;

  // Binding newly created socket to given IP and verification
  if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
  {
    printf("socket bind failed...\n");
    exit(0);
  }
  else
    printf("Create port..\n");

  socklen_t len = sizeof(servaddr);
  if (getsockname(sockfd, (struct sockaddr *)&servaddr, &len) == -1)
  {
    perror("getsockname");
  }

  sprintf(port, "%d", ntohs(servaddr.sin_port));
  close(sockfd);

  // To retrieve hostname
  hostname = gethostname(hostbuffer, sizeof(hostbuffer));
  checkHostName(hostname);

  // To retrieve host information
  host_entry = gethostbyname(hostbuffer);
  checkHostEntry(host_entry);

  // To convert an Internet network
  // address into ASCII string
  IPbuffer = inet_ntoa(*((struct in_addr *)
                             host_entry->h_addr_list[0]));

  // strcat(IPbuffer, "~");
  // strcat(IPbuffer, port);

  strcat(Port, port);

  return (Port);
}

char *return_ip(char ip_port[])
{
  char *IP;
  IP = (char *)calloc(80, sizeof(char));
  for (int i = 0; i < strlen(ip_port); i++)
  {
    IP[i] = ip_port[i];
    if (ip_port[i] == '~')
    {
      IP[i] = '\0';
      break;
    }
  }
  return (IP);
}

char *return_port(char ip_port[])
{
  char *Post;
  Post = (char *)calloc(80, sizeof(char));
  int check = 0, j = 0;
  for (int i = 0; i < strlen(ip_port); i++)
  {
    if (check == 1)
    {
      Post[j] = ip_port[i];
      j++;
    }
    if (ip_port[i] == '~')
      check = 1;
  }

  return (Post);
}

int isPositionExits(char location[])
{
  if (strcmp(location, "a1\n") == 0)
    if (pointBroad[0] != '0')
      return 1;
  if (strcmp(location, "a2\n") == 0)
    if (pointBroad[1] != '0')
      return 1;
  if (strcmp(location, "a3\n") == 0)
    if (pointBroad[2] != '0')
      return 1;
  if (strcmp(location, "b1\n") == 0)
    if (pointBroad[3] != '0')
      return 1;
  if (strcmp(location, "b2\n") == 0)
    if (pointBroad[4] != '0')
      return 1;
  if (strcmp(location, "b3\n") == 0)
    if (pointBroad[5] != '0')
      return 1;
  if (strcmp(location, "c1\n") == 0)
    if (pointBroad[6] != '0')
      return 1;
  if (strcmp(location, "c2\n") == 0)
    if (pointBroad[7] != '0')
      return 1;
  if (strcmp(location, "c3\n") == 0)
    if (pointBroad[8] != '0')
      return 1;
  return 0;
}

char *updateBroad(char pointBroad[], char location[], char player)
{
  if (strcmp(location, "a1\n") == 0)
    pointBroad[0] = player;
  if (strcmp(location, "a2\n") == 0)
    pointBroad[1] = player;
  if (strcmp(location, "a3\n") == 0)
    pointBroad[2] = player;
  if (strcmp(location, "b1\n") == 0)
    pointBroad[3] = player;
  if (strcmp(location, "b2\n") == 0)
    pointBroad[4] = player;
  if (strcmp(location, "b3\n") == 0)
    pointBroad[5] = player;
  if (strcmp(location, "c1\n") == 0)
    pointBroad[6] = player;
  if (strcmp(location, "c2\n") == 0)
    pointBroad[7] = player;
  if (strcmp(location, "c3\n") == 0)
    pointBroad[8] = player;

  return (pointBroad);
}

int checkWinner(char broad[], char xo)
{
  // check-row
  for (int i = 0; i < 3; i++)
  {
    if (broad[3 * i] == xo && broad[3 * i + 1] == xo && broad[3 * i + 2] == xo)
    {
      return 1;
    }
  }

  // check-column
  for (int i = 0; i < 3; i++)
  {
    if (broad[i] == xo && broad[3 + i] == xo && broad[6 + i] == xo)
    {
      return 1;
    }
  }

  // check Left-to-Right downward Diagonal
  if (broad[0] == xo && broad[4] == xo && broad[8] == xo)
    return 1;

  // Check Left-to-Right upward Diagonal
  if (broad[2] == xo && broad[4] == xo && broad[6] == xo)
    return 1;

  return 0;
}
