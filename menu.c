#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dico.h"

void menu(){
char test = 0;
while (test != 'q'){
  printf("Que voulez vous faire ? \n");
  printf("Test 1 : [1] ?");
  printf("Test 2 : [2] ?");
  printf("Test 3 : [3] ?");
  printf("Test 4 : [4] ?");
  printf("Test 5 : [5] ?");
  printf("Test 6 : [6] ?");
  printf("QUITTER : [q] ?");

  scanf("%d",test);
  switch(test){
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 'q':
      break;
    default:
      break;
  }
}

}
