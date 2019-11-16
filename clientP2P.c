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
  char *IPbuffer;
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

  strcat(IPbuffer, "~");
  strcat(IPbuffer, port);

  return (IPbuffer);
}

char *return_ip(char ip_port[])
{
  char *IP;
  IP = (char *)malloc(80 * sizeof(char));
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
  Post = (char *)malloc(80 * sizeof(char));
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
