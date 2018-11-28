#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dico.h"
//#include "test_travail_3.h"

/*
Le principe du test 3 est de tester les fonctions d'ajouts, de suppreissions,
et de possession des mots dans un dictionnaire, Itératives

*/


int test4(){

  printf("\n");
  printf("---------------------------------------------------------------\n");
  printf("\n");
  printf("TEST 4 : : Ajout, remove, contains rec \n");
  printf("\n");
  printf("---------------------------------------------------------------\n");
  printf("\n");

  dico d2 = create_dico();

  add_rec(d2,"ours",4);
  add_rec(d2,"ourson",6);
  add_rec(d2,"oursonne",8);
  add_rec(d2,"ourse",5);
  add_rec(d2,"brule",5);
  add_rec(d2,"brille",6);
  add_rec(d2,"bord",4);
  add_rec(d2,"bordeau",7);
  add_rec(d2,"bateau",6);
  add_rec(d2,"bonsoir",7);
  print_prefix(d2);


  printf("\n");
  printf("Retirons maintenant les mots ours et brule :\n");
  //printf("Retirons maintenant les mots en c :\n");
  printf("Cette fonction ne fonctionne pas pour le moment\n");
  printf("\n");

  remove_rec(d2,"ours",4);
  remove_rec(d2,"brule",5);
  print_prefix(d2);

  printf("Testons si cordial est dans le dico :");
  if(contains_rec(d2,"cordial",7)){
    printf("Cordial dans le dico \n");
  }else{
    printf("Cordial est absent du dico\n");
  }

  printf("Testons si bateau est un mot du dico :");
  if(contains_rec(d2,"bateau",6)){
    printf("bateau est un mot du dictionnaire\n");
  }else{
    printf("bateau est absent du dico\n");
  }

  destroy_dico(&d2);
  return 1;
}
