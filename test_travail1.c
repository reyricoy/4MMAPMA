#include "dico.h"

/*
Le principe du travail 1 était la création du dictionnaire
ainsi que sa destruction.

*/
int test1()
{
  dico dictionnaire;
  int test;

  dictionnaire=create_dico();

  test=destroy_dico(&dictionnaire);

  printf("Le dico a bien ete free [%d]",test);

}
