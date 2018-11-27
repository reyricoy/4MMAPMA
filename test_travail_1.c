#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dico.h"
//#include "test_travail_1.h"
/*
Le principe du travail 1 était la création du dictionnaire
ainsi que sa destruction.

*/
int test1()
{
  printf("\n");
  printf("TEST 1 : \n");
  dico dictionnaire;
  int test;

  dictionnaire=create_dico();

  test=destroy_dico(&dictionnaire);

  printf("Le dico a bien ete free [%d]",test);

  return test;
}
