#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dico.h"

void menu(){
int  test = 0;
while (test != 7){
  printf("\n");
  printf("---------------------------------------------------------------\n");
  printf("\n");
  printf("                              MENU\n");
  printf("\n");
  printf("---------------------------------------------------------------\n");
  printf("\n");
  printf("         Test 1 : [1]");
  printf("         Test 2 : [2]\n");
  printf("         Test 3 : [3]");
  printf("         Test 4 : [4]\n");
  printf("         Test 5 : [5]");
  printf("         Test 6 : [6]\n");
  printf("QUITTER : [7]\n");

  scanf("%d",&test);

  switch(test){
    case 1: printf("test 1 : %d\n", test1());
	return;
      break;
    case 2: printf("test 2 : %d\n", test2());
	return;
      break;
    case 3: printf("test 3 : %d\n", test3());
	return;
      break;
    case 4: printf("test 4 : %d\n", test4());
	return;
      break;
    case 5: printf("test 5 : %d\n", test5());
	return;
      break;
    case 6: printf("test 6 : %d\n", test6());
	return;
      break;
    case 7: printf("Merci, à bientôt !");
      break;
    default: printf("Choix invalide");
      test=7;
      break;
  }
  printf("\n");
}

}
