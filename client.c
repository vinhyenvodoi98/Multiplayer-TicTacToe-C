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
#include "clientPeer1.h"
#include "clientPeer2.h"

#define clear() printf("\033[H\033[J")

#define MAX 80
#define SA struct sockaddr

int loginTime = 3;
char name[20] = "";

void login(int sockfd)
{
  char buff[MAX], username[MAX];
  int n;
  bzero(buff, sizeof(buff));
  if (loginTime != 4)
  {
    printf("Enter username : ");
    strcat(buff, "1");
    n = 1;
    while ((buff[n++] = getchar()) != '\n')
      ;

    strcpy(username, buff);
    buff[n - 1] = '~';
    printf("Enter password : ");
    while ((buff[n++] = getchar()) != '\n')
      ;

    write(sockfd, buff, sizeof(buff));
    bzero(buff, sizeof(buff));

    read(sockfd, buff, sizeof(buff));

    if (loginTime < 4)
      if (strcmp(buff, "Login successfully") != 0)
        loginTime--;
      else
      {
        strcpy(name, username);
        for (int i = 0; i <= strlen(name); i++)
          name[i] = name[i + 1];
        name[strlen(name) - 1] = '\0';
        loginTime = 4;
      }

    if (loginTime == 0)
    {
      username[0] = '3';
      write(sockfd, username, sizeof(username));
      bzero(buff, sizeof(buff));
      read(sockfd, buff, sizeof(buff));
    }
    printf("From Server : %s\n", buff);
  }
  else
  {
    printf("You already login !\n");
  }
}

void signup(int sockfd)
{
  char buff[MAX], username[MAX];
  int n;
  bzero(buff, sizeof(buff));

  printf("Enter username : ");
  strcat(buff, "4"); //set for logout
  n = 1;
  while ((buff[n++] = getchar()) != '\n')
    ;

  strcpy(username, buff);
  buff[n - 1] = '~';
  printf("Enter password : ");
  while ((buff[n++] = getchar()) != '\n')
    ;

  write(sockfd, buff, sizeof(buff));
  bzero(buff, sizeof(buff));

  read(sockfd, buff, sizeof(buff));

  if (strcmp(buff, "Signup successfully") == 0)
  {
    strcpy(name, username);
    for (int i = 0; i <= strlen(name); i++)
      name[i] = name[i + 1];
    name[strlen(name) - 1] = '\0';
    loginTime = 4;
  }

  printf("From Server : %s\n", buff);
}

void logout(int sockfd)
{
  char buff[MAX];
  int n;
  bzero(buff, sizeof(buff));
  printf("Enter username : ");
  strcat(buff, "2");
  n = 1;
  while ((buff[n++] = getchar()) != '\n')
    ;

  write(sockfd, buff, sizeof(buff));
  bzero(buff, sizeof(buff));
  read(sockfd, buff, sizeof(buff));
  if (strcmp(buff, "Goodbye") == 0)
    loginTime = 3;
  printf("From Server : %s\n", buff);
}

void normalgame(int sockfd)
{
  int a, iPort;
  char buff[MAX], *ip_port, *ip, *cPort;
  bzero(&buff, sizeof(buff));

  ip_port = (char *)calloc(80, sizeof(char));
  ip = (char *)calloc(20, sizeof(char));
  cPort = (char *)calloc(10, sizeof(char));

  strcpy(ip_port, genPort());
  strcat(buff, "5");
  strcat(buff, ip_port);

  write(sockfd, buff, sizeof(buff));

  bzero(buff, sizeof(buff));

  read(sockfd, buff, sizeof(buff));
  if (buff[0] == 'h')
  {
    for (int i = 0; i < strlen(buff); i++)
      buff[i] = buff[i + 1];
    strcpy(ip, buff);
    iPort = atoi(ip_port);
    startP2P(ip, iPort, 1, name, sockfd);
  }
  else
  {
    strcat(ip, return_ip(buff));
    strcat(cPort, return_port(buff));
    iPort = atoi(cPort);
    connectP2P(ip, iPort, 1, name, sockfd);
  }
}

void rankgame(int sockfd, char name[])
{
  int a, iPort;
  char buff[MAX], *ip_port, *ip, *cPort;
  bzero(&buff, sizeof(buff));

  ip_port = (char *)calloc(80, sizeof(char));
  ip = (char *)calloc(20, sizeof(char));
  cPort = (char *)calloc(10, sizeof(char));

  strcpy(ip_port, genPort());
  strcat(buff, "6");
  strcat(buff, ip_port);

  write(sockfd, buff, sizeof(buff));

  bzero(buff, sizeof(buff));

  read(sockfd, buff, sizeof(buff));
  if (buff[0] == 'h')
  {
    for (int i = 0; i < strlen(buff); i++)
      buff[i] = buff[i + 1];
    strcpy(ip, buff);
    iPort = atoi(ip_port);
    startP2P(ip, iPort, 2, name, sockfd);
  }
  else
  {
    strcat(ip, return_ip(buff));
    strcat(cPort, return_port(buff));
    iPort = atoi(cPort);
    connectP2P(ip, iPort, 2, name, sockfd);
  }
}

void showRank(int sockfd, char name[])
{
  int a;
  char buff[MAX], rank[500];
  bzero(buff, sizeof(buff));
  strcat(buff, "7");
  strcat(buff, name);

  write(sockfd, buff, sizeof(buff));

  // bzero(buff, sizeof(buff));

  read(sockfd, rank, sizeof(rank));
  rankNav();
  printf("%s", rank);
  getchar();
}

void gameScreen(int sockfd)
{
  char d;
  while (1)
  {
    clear();
    gameMenu(name);
    scanf("%c", &d);

    if (d == '1')
    {
      scanf("%*c");
      normalgame(sockfd);
    }
    if (d == '2')
    {
      scanf("%*c");
      rankgame(sockfd, name);
    }
    if (d == '3')
    {
      scanf("%*c");
      showRank(sockfd, name);
    }
    if (d == '4')
    {
      scanf("%*c");
      clear();
      info(name);
    }
    if (d == 'q')
    {
      scanf("%*c");
      logout(sockfd);
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;
  char ipAddress[15];
  unsigned short PORT;

  if (argc < 2 || argc > 3)
  {
    printf("hay nhap chuoi theo cu phap \n ./client 3asd15 \n ");
    return 0;
  }

  strcpy(ipAddress, argv[1]);
  PORT = atoi(argv[2]);

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
  servaddr.sin_addr.s_addr = inet_addr(ipAddress);
  servaddr.sin_port = htons(PORT);

  // connect the client socket to server socket
  if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
  {
    printf("connection with the server failed...\n");
    exit(0);
  }
  else
    printf("connected to the server..\n");

  char c, d;
  int check = 0;

  while (1)
  {
    if (loginTime >= -1)
    {
      if (loginTime == 4)
        gameScreen(sockfd);

      clear();
      loginMenu();
      scanf("%c", &c);

      if (c == '1')
      {
        scanf("%*c");
        login(sockfd);
      }
      if (c == '2')
      {
        scanf("%*c");
        signup(sockfd);
      }
      if (c != '2' && c != '1')
        break;
    }
  }
  // close the socket
  close(sockfd);
}
