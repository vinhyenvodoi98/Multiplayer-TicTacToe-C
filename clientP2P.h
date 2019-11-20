#ifndef __FILE_H__
#define __FILE_H__

char pointBroad[9];

char *genPort();
char *return_ip(char ip_port[]);
char *return_port(char ip_port[]);
int isPositionExits(char location[]);
char *updateBroad(char pointBroad[], char location[], char player);
int checkWinner(char broad[], char xo);

#endif
