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
  strcpy(pointBroad, "000000000");
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

      if (!isPositionExits(buff))
        break;
    }
    strcpy(pointBroad, updateBroad(pointBroad, buff, '2'));
    clear();
    ingame(pointBroad);
    write(sockfd, buff, sizeof(buff));

    if (checkWinner(pointBroad, '2'))
    {
      printf("Ban da chien thang !!!");
      getchar();
      close(sockfd);
      break;
    }

    bzero(buff, sizeof(buff));
    printf("Doi doi phuong danh ...\n");
    read(sockfd, buff, sizeof(buff));
    strcpy(pointBroad, updateBroad(pointBroad, buff, '1'));

    if (checkWinner(pointBroad, '1'))
    {
      printf("Ban da thua cuoc !!!");
      getchar();
      close(sockfd);
      break;
    }
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
