#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dico.h"
//#include "test_travail_5.h"

/*
Le principe du TRAVAIL 5 etait d'ecrire les fonctions de
d'impressions d'un dictionnaire.

Tout d'abord une fonction pour savoir le nombre de mots du dictionnaire.

Puis une fonction pour imprimer les mots un par un du dictionnaire.

*/



int test5()
{
  printf("\n");
  printf("TEST 5 : \n");
  dico dictionnaire1 = create_dico();
  int nbmots1,nbmots2;
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
  nbmots1=nb_words(dictionnaire1);
  print_dico(dictionnaire1);
  remove_rec(dictionnaire1,"oursonne",8);
  remove_rec(dictionnaire1,"brule",5);
  remove_rec(dictionnaire1,"bateau",6);
  nbmots2=nb_words(dictionnaire1);
  print_dico(dictionnaire1);
  printf("Le nombre de mots avant les remove est: [%d] et après: [%d]\n",nbmots1,nbmots2);
  return 1;
}
