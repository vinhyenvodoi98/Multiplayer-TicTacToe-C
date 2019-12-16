#include <stdio.h>

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

void nav(char name[])
{
  printf("+-----------------------------------------------------------+\n");
  blue();
  printf("  TicTacToe 1.0-beta");
  reset();
  yellow();
  printf("                                 %s\n", name);
  reset();
  printf("+-----------------------------+-----------------------------+\n");
}

void printXO(char XO)
{
  if (XO == '1')
  {
    red();
    printf("O");
    reset();
  }
  else if (XO == '2')
  {
    blue();
    printf("X");
    reset();
  }
  else
  {
    printf(" ");
  }
}

void playerBroad(char broad[])
{
  red();
  printf("            G-A-M-E           ");
  reset();
  printf("|");
  red();
  printf("             TOA DO             \n");
  reset();
  printf("             |   |            |             |    |           \n");
  printf("          ");
  printXO(broad[0]);
  printf("  | ");
  printXO(broad[1]);
  printf(" |  ");
  printXO(broad[2]);
  printf("         |          \033[1;34ma1\033[0m | \033[1;34ma2\033[0m | \033[1;34ma3\033[0m        \n");
  printf("        -----|---|-----       |        -----|----|-----      \n");
  printf("          ");
  printXO(broad[3]);
  printf("  | ");
  printXO(broad[4]);
  printf(" |  ");
  printXO(broad[5]);
  printf("         |          \033[1;34mb1\033[0m | \033[1;34mb2\033[0m | \033[1;34mb3\033[0m        \n");
  printf("        -----|---|-----       |        -----|----|-----      \n");
  printf("          ");
  printXO(broad[6]);
  printf("  | ");
  printXO(broad[7]);
  printf(" |  ");
  printXO(broad[8]);
  printf("         |          \033[1;34mc1\033[0m | \033[1;34mc2\033[0m | \033[1;34mc3\033[0m        \n");
  printf("             |   |            |             |    |           \n");
}

void score(char name1[], char name2[])
{
  printf("+-----------------------------+-----------------------------+\n");
  red();
  printf(" Match: ");
  reset();
  blue();
  printf(" %s", name1);
  reset();
  yellow();
  printf(" vs");
  reset();
  blue();
  printf(" %s", name2);
  reset();
  printf(".                               \n");
  printf("+-----------------------------------------------------------+\n");
}

void ingame(char broadGame[])
{
  nav("");
  playerBroad(broadGame);
  // score();
}

void gameMenu(char name[])
{
  nav(name);
  printf("\n");
  printf("    [ ");
  red();
  printf("MAIN MENU");
  reset();
  printf(" ]\n\n");
  printf("    (\033[1;31m1\033[0m) Danh thuong\n");
  printf("    (\033[1;31m2\033[0m) Danh xep hang\n");
  printf("    (\033[1;31m3\033[0m) Xem thu hang\n\n");

  printf("    (\033[1;31m4\033[0m) Gioi thieu ve tro choi\n");
  printf("    (\033[1;31mq\033[0m) Quit\n");
}

void info(char name[])
{
  char a;
  nav(name);
  printf("Voi niem dam me cac game co dien Studio \033[1;34mLao Hac 1977\033[0m dem \n");
  printf("lai cho cac ban trai nghiem choi game \033[1;34mTicTacToe\033[0m chay tren \n");
  printf("he dieu hanh Linux voi giao dien than thien de choi. Ban   \n");
  printf("co the choi vs cac ban cua minh thong qua internet (su dung \n");
  printf("ket noi TCP/IP). Tat ca nhung gi ban phai lam la tao 1  \n");
  printf("room moi nguoi se tham gia room cua ban. Hoac ban co the \n");
  printf("tham gia room cua nguoi khac de bat dau tro choi.\n");
  printf("neu trong luc choi ban muon thoat hay nhan phim q. \n\n");
  blue();
  printf("TicTacToe beta-1.0\n\n");
  reset();
  printf("Press \033[1;31menter\033[0m de quay ve man hinh chinh\n");
  scanf("%c", &a);
}

void loginMenu()
{
  nav("");
  printf("\n");
  printf("    [ ");
  red();
  printf("USER MANAGEMENT");
  reset();
  printf(" ]\n\n");

  printf("    (\033[1;31m1\033[0m) Dang nhap\n");
  printf("    (\033[1;31m2\033[0m) Dang ki\n\n");
  printf("    (1-2, other to \033[1;34mquit\033[0m):\n");
}

void rankNav()
{
  printf("+-----------------------------------------------------------+\n");
  red();
  printf("RANK\t");
  reset();
  red();
  printf("PLAYER\t");
  reset();
  red();
  printf("WIN\t");
  reset();
  red();
  printf("LOSE\t");
  reset();
  red();
  printf("WIN/LOSE\n");
  reset();
  printf("+-----------------------------------------------------------+\n");
}