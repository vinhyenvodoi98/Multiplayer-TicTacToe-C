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

void joinPerson(int sockfd, int typeOfGame, char name[], int connectserver)
{
  strcpy(pointBroad, "000000000");
  char buff[MAX], msg[MAX];
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
      if (typeOfGame == 2)
      {
        bzero(buff, MAX);
        bzero(msg, MAX);
        read(sockfd, buff, sizeof(buff));
        strcat(msg, "6~");
        strcat(msg, name);
        strcat(msg, "~");
        strcat(msg, buff);
        write(connectserver, msg, sizeof(msg));
        read(connectserver, msg, sizeof(msg));
        bzero(msg, MAX);
        printf("%s", msg);
      }
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
      if (typeOfGame == 2)
      {
        strcpy(buff, name);
        write(sockfd, buff, sizeof(buff));
      }
      getchar();
      close(sockfd);
      break;
    }
  }
}

void connectP2P(char ip[], int PORT, int typeOfGame, char name[], int connectserver)
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

  // Function for chatting between client and server
  // typeOfGame ==1 -> nomarl game
  // typeOfGame ==2 -> rank game
  joinPerson(sockfd, typeOfGame, name, connectserver);

  close(sockfd);
}
