#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dico.h"

void menu(){
int  test = 0;
while (test != 'q'){
  printf("Que voulez vous faire ? \n");
  printf("Test 1 : [1] ?");
  printf("Test 2 : [2] ?");
  printf("Test 3 : [3] ?");
  printf("Test 4 : [4] ?");
  printf("Test 5 : [5] ?");
  printf("Test 6 : [6] ?");
  printf("QUITTER : [q] ?");

  scanf("%d",&test);

  switch(test){
    case 1: printf("test 1 : %d\n", test1());
      break;
    case 2: printf("test 2 : %d\n", test2());
      break;
    case 3: printf("test 3 : %d\n", test3());
      break;
    case 4:
      break;
    case 5: printf("test 5 : %d\n", test5());
      break;
    case 6: printf("test 6 : %d\n", test6());
      break;
    case 'q':
      break;
    default:
      break;
  }
}

}
