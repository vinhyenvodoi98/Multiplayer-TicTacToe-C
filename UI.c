#include <stdio.h>

#define clear() printf("\033[H\033[J")

void red()
{
  printf("\033[1;31m");
}

void yellow()
{
  printf("\033[1;33m");
}

void blue()
{
  printf("\033[1;34m");
}

void reset()
{
  printf("\033[0m");
}

void nav()
{
  printf("+-----------------------------------------------------------+\n");
  printf("| ");
  blue();
  printf("TicTacToe 1.0-beta");
  reset();
  printf("                                        |\n");
  printf("+-----------------------------+-----------------------------+\n");
}

void menu()
{
}

void broad()
{
  red();
  printf("            G-A-M-E             ");
  reset();
  printf("|");
  red();
  printf("             TOA DO             \n");
  reset();
  printf("             |   |            +             |    |           \n");
  printf("             |   |            +          \033[1;34ma1\033[0m | \033[1;34ma2\033[0m | \033[1;34ma3\033[0m        \n");
  printf("        -----|---|-----       +        -----|----|-----      \n");
  printf("             |   |            +          \033[1;34mb1\033[0m | \033[1;34mb2\033[0m | \033[1;34mb3\033[0m        \n");
  printf("        -----|---|-----       +        -----|----|-----      \n");
  printf("             |   |            +          \033[1;34mc1\033[0m | \033[1;34mc2\033[0m | \033[1;34mc3\033[0m        \n");
  printf("             |   |            +             |    |           \n");
}

void score()
{
  char name1[20] = "Do Hoang", name2[20] = "Tran Dan";
  int score1 = 1, score2 = 0;
  printf("+-----------------------------+-----------------------------+\n");
  printf("|");
  red();
  printf(" Score:");
  reset();
  blue();
  printf(" %s", name1);
  reset();
  printf(" %d,", score1);
  blue();
  printf(" %s", name2);
  reset();
  printf(" %d.                            |\n", score2);
  printf("+-----------------------------------------------------------+\n");
}

int main()
{
  nav();
  broad();
  score();
  return 0;
}
// clear();