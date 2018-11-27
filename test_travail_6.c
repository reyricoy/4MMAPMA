#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dico.h"
//#include "test_travail_6.h"

/*

*/



int test6()
{
  printf("\n");
  printf("---------------------------------------------------------------\n");
  printf("\n");
  printf("TEST 6 : L'itérateur \n");
  printf("\n");
  printf("---------------------------------------------------------------\n");
  printf("\n");
  
  dico dictionnaire1 = create_dico();
  add_rec(dictionnaire1,"ours",4);
  add_rec(dictionnaire1,"ourson",6);
  add_rec(dictionnaire1,"oursonne",8);
  add_rec(dictionnaire1,"ourse",5);
  add_rec(dictionnaire1,"brule",5);
  add_rec(dictionnaire1,"brille",6);
  add_rec(dictionnaire1,"bord",4);
  add_rec(dictionnaire1,"bordeau",7);
  add_rec(dictionnaire1,"bateau",6);
  add_rec(dictionnaire1,"bonsoir",7);

  iterator * dit = start_iterator(dictionnaire1);
  while (has_next(dit))
  {
   printf("-%s", next(dit));
  }
  printf("\n");
  destroy_iterator(&dit);
  destroy_dico(&dictionnaire1);
  return 1;
}
