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
  printf("---------------------------------------------------------------\n");
  printf("\n");
  printf("TEST 5 : Nb mots du dico et Affichage 1 par 1\n");
  printf("\n");
  printf("---------------------------------------------------------------\n");
  printf("\n");

  dico dictionnaire3 = create_dico();
  int nbmots1,nbmots2;
  add_rec(dictionnaire3,"ours",4);
  add_rec(dictionnaire3,"ourson",6);
  add_rec(dictionnaire3,"oursonne",8);
  add_rec(dictionnaire3,"ourse",5);
  add_rec(dictionnaire3,"brule",5);
  add_rec(dictionnaire3,"brille",6);
  add_rec(dictionnaire3,"bord",4);
  add_rec(dictionnaire3,"bordeau",7);
  add_rec(dictionnaire3,"bateau",6);
  add_rec(dictionnaire3,"bonsoir",7);
  nbmots1=nb_words(dictionnaire3);
  print_prefix(dictionnaire3);
  print_dico(dictionnaire3);
  remove_rec(dictionnaire3,"oursonne",8);
  remove_rec(dictionnaire3,"brule",5);
  remove_rec(dictionnaire3,"bateau",6);
  nbmots2=nb_words(dictionnaire3);
  print_dico(dictionnaire3);
  printf("Le nombre de mots avant les remove est: [%d] et après: [%d]\n",nbmots1,nbmots2);
  destroy_dico(&dictionnaire3);
  return 1;
}
