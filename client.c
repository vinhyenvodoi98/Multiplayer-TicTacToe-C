#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <fcntl.h>  // for open
#include <unistd.h> // for close
#include <netdb.h>
#include <string.h>

#define MAX 80
#define SA struct sockaddr

int loginTime = 3;

void printfMenu()
{
  printf("USER MANAGEMENT PROGRAM\n");
  printf("-----------------------------------\n");
  printf("1. Sign in\n");
  printf("2. Sign out\n");
  printf("Your choice (1-2, other to quit):\n");
}

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
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);

  // connect the client socket to server socket
  if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
  {
    printf("connection with the server failed...\n");
    exit(0);
  }
  else
    printf("connected to the server..\n");

  char c;
  int check = 0;

  while (1)
  {
    if (loginTime >= -1)
    {
      printfMenu();
      scanf("%c", &c);

      if (c == '1')
      {
        scanf("%*c");
        login(sockfd);
      }
      if (c == '2')
      {
        scanf("%*c");
        logout(sockfd);
      }
      if (c != '2' && c != '1')
        break;
    }
  }
  // close the socket
  close(sockfd);
}