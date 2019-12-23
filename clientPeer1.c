#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <fcntl.h>  // for open
#include <unistd.h> // for close
#include <netdb.h>
#include <string.h>
#include "UI.h"
#include "clientP2P.h"

#define MAX 80
#define SA struct sockaddr
#define clear() printf("\033[H\033[J")

void hostPerson(int sockfd, int typeOfGame, char name[], int connectserver)
{
  strcpy(pointBroad, "000000000");

  char buff[MAX], msg[MAX], competitorName[MAX];
  int n;

  bzero(buff, MAX);
  bzero(competitorName, MAX);

  if (typeOfGame == 2)
  {
    strcpy(buff, name);
    write(sockfd, buff, sizeof(buff));
    read(sockfd, competitorName, sizeof(competitorName));
  }
  // infinite loop for game

  for (;;)
  {
    bzero(buff, MAX);
    clear();

    ingame(pointBroad);
    if (typeOfGame == 2)
      score(name, competitorName);
    printf("Doi doi phuong danh ...\n");
    // read the message from client and copy it in buffer
    if (read(sockfd, buff, sizeof(buff)) == 0)
    {
      if (typeOfGame == 2)
      {
        bzero(msg, MAX);
        strcat(msg, "6~");
        strcat(msg, name);
        strcat(msg, "~");
        strcat(msg, competitorName);

        write(connectserver, msg, sizeof(msg));
        read(connectserver, msg, sizeof(msg));

        bzero(msg, MAX);
        printf("%s", msg);
      }
      printf("\n Ban da chien thang do nguoi choi kia da bo cuoc !!!");
      getchar();
      close(sockfd);
      break;
    }

    // print buffer which contains the client contents
    strcpy(pointBroad, updateBroad(pointBroad, buff, '2'));
    clear();
    ingame(pointBroad);
    if (typeOfGame == 2)
      score(name, competitorName);

    if (checkWinner(pointBroad, '2'))
    {
      bzero(buff, MAX);
      printf("Ban da thua cuoc !!!");

      getchar();
      close(sockfd);
      break;
    }
    // copy server message in the buffer
    printf("Nhap vi tri muon danh : ");
    while (1)
    {
      bzero(buff, MAX);

      n = 0;
      while ((buff[n++] = getchar()) != '\n')
        ;

      if (!isPositionExits(buff))
        break;
    }

    if (strcmp(buff, "q\n") == 0)
    {
      close(sockfd);
      break;
    }
    // and send that buffer to client
    write(sockfd, buff, sizeof(buff));
    strcpy(pointBroad, updateBroad(pointBroad, buff, '1'));
    if (checkWinner(pointBroad, '1'))
    {
      printf("Ban da chien thang !!!");
      if (typeOfGame == 2)
      {
        bzero(msg, MAX);
        strcat(msg, "6~");
        strcat(msg, name);
        strcat(msg, "~");
        strcat(msg, competitorName);

        write(connectserver, msg, sizeof(msg));
        read(connectserver, msg, sizeof(msg));

        bzero(msg, MAX);
        printf("%s", msg);
      }
      getchar();
      close(sockfd);
      break;
    }
  }
}

void startP2P(char ip[], int PORT, int typeOfGame, char name[], int connectserver)
{
  int sockfd, connfd, len;
  struct sockaddr_in servaddr, cli;

  // socket create and verification
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

  printf("ip port: %s:%d___", ip, PORT);

  // Binding newly created socket to given IP and verification
  if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
  {
    printf("socket bind failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully binded..\n");

  // Now server is ready to listen and verification
  if ((listen(sockfd, 5)) != 0)
  {
    printf("Listen failed...\n");
    exit(0);
  }
  else
    printf("Waiting another player ...\n");
  len = sizeof(cli);

  // Accept the data packet from client and verification
  connfd = accept(sockfd, (SA *)&cli, &len);
  if (connfd < 0)
  {
    printf("server acccept failed...\n");
    exit(0);
  }
  else
    printf("server acccept the client...\n");

  // Function for chatting between client and server
  // typeOfGame ==1 -> nomarl game
  // typeOfGame ==2 -> rank game
  hostPerson(connfd, typeOfGame, name, connectserver);

  close(sockfd);
}
