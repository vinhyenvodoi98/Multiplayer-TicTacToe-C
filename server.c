#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>  // for open
#include <unistd.h> // for close
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include "serverService.h"
#include "file.h"

#define MAX 80
#define SA struct sockaddr

char currentGame[MAX];
char rankGame[MAX];

int msg(int sockfd, char ip[])
{
  char buffer[MAX], number[MAX], charactor[MAX], msg[MAX], username[MAX], password[MAX], win[MAX], lose[MAX];

  int n, i, j, sendlong = 0;

  // listen client
  bzero(buffer, MAX);
  bzero(number, MAX);
  bzero(charactor, MAX);
  bzero(msg, MAX);
  bzero(username, MAX);
  bzero(password, MAX);
  bzero(win, MAX);
  bzero(lose, MAX);
  if (read(sockfd, buffer, sizeof(buffer)) != 0)
  {
    printf("From client: %s To client : ", buffer);
    if (buffer[0] == '1') //for login
    {
      for (i = 0; i < strlen(buffer); i++)
      {
        if (buffer[i + 1] == '~')
          break;
        username[i] = buffer[i + 1];
      }

      for (j = 0; j < strlen(buffer); j++)
      {
        if (buffer[i] == '\n')
          break;
        password[j] = buffer[i + 2];
        i++;
      }
      password[j - 2] = '\0';
      strcat(msg, _signin(username, password));
      msg[strlen(msg)] = '\0';
      printf("%s\n", msg);
    }

    else if (buffer[0] == '2') //for logout
    {
      for (i = 0; i < strlen(buffer); i++)
        username[i] = buffer[i + 1];

      username[strlen(username) - 1] = '\0';
      strcat(msg, _signout(username));
    }

    else if (buffer[0] == '3') //for lockAccout
    {
      for (i = 0; i < strlen(buffer); i++)
        username[i] = buffer[i + 1];

      username[strlen(username) - 1] = '\0';
      strcat(msg, _lockAccount(username));
    }

    else if (buffer[0] == '4') // for signup
    {
      for (i = 0; i < strlen(buffer); i++)
      {
        if (buffer[i + 1] == '~')
          break;
        username[i] = buffer[i + 1];
      }

      for (j = 0; j < strlen(buffer); j++)
      {
        if (buffer[i] == '\n')
          break;
        password[j] = buffer[i + 2];
        i++;
      }
      password[j - 2] = '\0';
      strcat(msg, _signup(username, password));
      msg[strlen(msg)] = '\0';
      printf("%s\n", msg);
    }

    else if (buffer[0] == '5') // for create normal game
    {
      for (i = 0; i < strlen(buffer); i++)
        buffer[i] = buffer[i + 1];

      if (strlen(currentGame) == 0)
      {
        strcat(currentGame, ip);
        strcat(currentGame, "~");
        strcat(currentGame, buffer);
        printf("ip %s\n", currentGame);
        strcat(msg, "h");
        strcat(msg, ip);
      }
      else
      {
        strcat(msg, currentGame);
        bzero(currentGame, MAX);
      }
    }
    else if (buffer[0] == '6') // for create rank game
    {
      // printf("%s\n", buffer);

      for (i = 0; i < strlen(buffer); i++)
        buffer[i] = buffer[i + 1];

      if (buffer[0] == '~')
      {
        for (i = 0; i < strlen(buffer); i++)
          buffer[i] = buffer[i + 1];

        for (i = 0; i < strlen(buffer); i++)
        {
          if (buffer[i] == '~')
            break;
          win[i] = buffer[i];
        }

        for (j = 0; j < strlen(buffer); j++)
        {
          if (buffer[i] == '\n')
            break;
          lose[j] = buffer[i + 1];
          i++;
        }
        lose[j - 2] = '\0';
        updateWinLose(win, lose);
        strcat(msg, "update done");
      }
      else
      {
        if (strlen(rankGame) == 0)
        {
          strcat(rankGame, ip);
          strcat(rankGame, "~");
          strcat(rankGame, buffer);
          printf("ip %s\n", rankGame);
          strcat(msg, "h");
          strcat(msg, ip);
        }
        else
        {
          strcat(msg, rankGame);
          bzero(rankGame, MAX);
        }
      }
    }
    else if (buffer[0] == '7')
    {
      char rank[500];
      bzero(rank, 500);
      for (i = 0; i < strlen(buffer); i++)
        buffer[i] = buffer[i + 1];

      strcat(rank, _getRank(buffer));
      printf("\n%s ", rank);
      sendlong = 1;
      write(sockfd, rank, sizeof(rank));
    }
    if (!sendlong)
      write(sockfd, msg, sizeof(msg));
    sendlong = 0;
    memset(msg, 0, sizeof(msg));
    return 1;
  }
  else
  {
    return 0;
  }
}

// Driver function
int main(int argc, char *argv[])
{
  int16_t PORT;
  int sockfd, connfd, len;
  struct sockaddr_in servaddr, address;

  int opt = 1;
  int addrlen, new_socket, client_socket[30],
      max_clients = 30, activity, i, valread, sd;
  int max_sd;

  char buffer[50];

  //set of socket descriptors
  fd_set readfds;

  if (argc != 2)
  {
    PORT = 8080;
  }
  else
  {
    PORT = atoi(argv[1]);
  }

  //initialise all client_socket[] to 0 so not checked
  for (i = 0; i < max_clients; i++)
  {
    client_socket[i] = 0;
  }

  printf("listen port 127.0.0.1:%s \n", argv[1]);
  printf("Press Ctrl+C to close\n");

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

  // setup multiconnect
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                 sizeof(opt)) < 0)
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  addrlen = sizeof(servaddr);

  // Binding newly created socket to given IP and verification
  if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
  {
    printf("socket bind failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully binded..\n");

  // Now server is ready to listen and verification
  if ((listen(sockfd, 3)) != 0)
  {
    printf("Listen failed...\n");
    exit(0);
  }
  else
    printf("Server listening..\n");

  readFile();

  while (1)
  {
    //clear the socket set
    FD_ZERO(&readfds);

    //add master socket to set
    FD_SET(sockfd, &readfds);
    max_sd = sockfd;

    //add child sockets to set
    for (i = 0; i < max_clients; i++)
    {
      //socket descriptor
      sd = client_socket[i];

      //if valid socket descriptor then add to read list
      if (sd > 0)
        FD_SET(sd, &readfds);

      //highest file descriptor number, need it for the select function
      if (sd > max_sd)
        max_sd = sd;
    }

    //wait for an activity on one of the sockets , timeout is NULL ,
    //so wait indefinitely
    activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

    if ((activity < 0) && (errno != EINTR))
    {
      printf("select error");
    }

    //If something happened on the master socket ,
    //then its an incoming connection
    if (FD_ISSET(sockfd, &readfds))
    {
      if ((new_socket = accept(sockfd,
                               (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
      {
        perror("accept");
        exit(EXIT_FAILURE);
      }

      //inform user of socket number - used in send and receive commands
      printf("New connection , socket fd is %d , ip is : %s , port : %d \n ", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

      //add new socket to array of sockets
      for (i = 0; i < max_clients; i++)
      {
        //if position is empty
        if (client_socket[i] == 0)
        {
          client_socket[i] = new_socket;
          printf("Adding to list of sockets as %d\n", i);
          break;
        }
      }
    }

    //else its some IO operation on some other socket
    for (i = 0; i < max_clients; i++)
    {
      sd = client_socket[i];

      if (FD_ISSET(sd, &readfds))
      {
        if (msg(sd, inet_ntoa(address.sin_addr)) == 0)
        {
          getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
          printf("\nHost disconnected , ip %s , port %d \n",
                 inet_ntoa(address.sin_addr), ntohs(address.sin_port));
          close(sd);
          client_socket[i] = 0;
        }
      }
    }
  }
  close(sockfd);
}
