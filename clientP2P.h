#ifndef __FILE_H__
#define __FILE_H__

int *pointBroad;

char *genPort();
char *return_ip(char ip_port[]);
char *return_port(char ip_port[]);
int isPositionExits(char location[], int *pointBroad);
void updateBroad(char location[], int player, int *pointBroad);

#endif