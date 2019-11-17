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

#include "UI.h"
#include "clientP2P.h"

#define MAX 80
#define SA struct sockaddr
#define clear() printf("\033[H\033[J")

void joinPerson(int sockfd)
{
  pointBroad = (int *)calloc(9, sizeof(int));
  for (int i = 0; i < 9; i++)
    pointBroad[i] = 0;

  char buff[MAX];
  int n;
  for (;;)
  {
    clear();
    ingame(pointBroad);

    printf("Nhap vi tri muon danh : ");

    while (1)
    {
      bzero(buff, sizeof(buff));
      n = 0;
      while ((buff[n++] = getchar()) != '\n')
        ;

      if (!isPositionExits(buff, pointBroad))
        break;
    }
    updateBroad(buff, 2, pointBroad);
    clear();
    ingame(pointBroad);

    write(sockfd, buff, sizeof(buff));
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    updateBroad(buff, 1, pointBroad);
  }
}

void connectP2P(char ip[], int PORT)
{
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  // socket create and varification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    printf("socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(ip);
  servaddr.sin_port = htons(PORT);

  // connect the client socket to server socket
  if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
  {
    printf("connection with the server failed...\n");
    exit(0);
  }
  else
    printf("connected to the server..\n");

  // function for chat
  joinPerson(sockfd);
  close(sockfd);
}
