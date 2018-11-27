#include "dico.h"

/*
Le principe du TRAVAIL 5 etait d'ecrire les fonctions de
d'impressions d'un dictionnaire.

Tout d'abord une fonction pour savoir le nombre de mots du dictionnaire.

Puis une fonction pour imprimer les mots un par un du dictionnaire.

*/



int test5()
{
  dico dictionnaire1;
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
  nbmots1=nb_mots(dictionnaire1);
  print_dico(dictionnaire1);
  remove_rec(dictionnaire1,"oursonne",8);
  remove_rec(dictionnaire1,"brule",5);
  remove_rec(dictionnaire1,"bateau",6);
  nbmots2=nb_mots(dictionnaire1);
  print_dico(dictionnaire1);
  printf("Le nombre de mots avant les remove est: [%d] et après: [%d]\n",nbmots1,nbmots2);
}
