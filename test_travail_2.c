#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dico.h"
//#include "test_travail_2.h"
/*
Le principe du TRAVAIL 2 etait d'ecrire les primitives de
manipulation d'un dictionnaire.

Savoir le nombre de feuilles, de noeuds et la hauteur du dictionnaire.

Pouvoir imprimer toutes les lettres du dictionnaire

Pouvoir dire si deux dictionnaire sont egaux.
*/

int test2()
{
  printf("\n");
  printf("TEST 2 : \n");
  bool test1,test2;
  dico dictionnaire1, dictionnaire2;
  dictionnaire1=create_dico();
  dictionnaire2=create_dico();
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
  printf("IMPRESSION DU DICTIONNAIRE\n");
  print_prefix(dictionnaire1);
  printf("NOMBRE DE NOEUDS DU DICO: [%d]\n",nb_nodes(dictionnaire1));
  printf("HAUTEUR DU DICO: [%d] \n",height(dictionnaire1));
  printf("NB D'ENFANTS DE DICO[14] (Celui qui a O): [%d]",nb_children(dictionnaire1[14]));
  add_rec(dictionnaire2,"ours",4);
  add_rec(dictionnaire2,"ourson",6);
  add_rec(dictionnaire2,"oursonne",8);
  add_rec(dictionnaire2,"ourse",5);
  add_rec(dictionnaire2,"brule",5);
  add_rec(dictionnaire2,"brille",6);
  add_rec(dictionnaire2,"bord",4);
  add_rec(dictionnaire2,"bordeau",7);
  add_rec(dictionnaire2,"bateau",6);
  add_rec(dictionnaire2,"bonsoir",7);
  test1=equals(dictionnaire1,dictionnaire2);
  remove_rec(dictionnaire2,"ours",4);
  test2=equals(dictionnaire1,dictionnaire2);
  printf("EGALITE DES DEUX DICTIONNAIRES AVANT [%d] ET APRES [%d]\n",test1,test2);
  return 1;
}
