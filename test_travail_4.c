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
  
  dico d = create_dico();

  add_rec(d,"ours",4);
  add_rec(d,"ourson",6);
  add_rec(d,"oursonne",8);
  add_rec(d,"ourse",5);
  add_rec(d,"brule",5);
  add_rec(d,"brille",6);
  add_rec(d,"bord",4);
  add_rec(d,"bordeau",7);
  add_rec(d,"bateau",6);
  add_rec(d,"bonsoir",7);
  print_prefix(d);


  printf("\n");
  printf("Retirons maintenant les mots ours et brule :\n");
  //printf("Retirons maintenant les mots en c :\n");
  printf("Cette fonction ne fonctionne pas pour le moment\n");
  printf("\n");
  /*
  remove_rec(d,"ours",4);
  remove_rec(d,"brule",5);
  print_prefix(d);
*/
  printf("Testons si cordial est dans le dico :");
  if(contains_rec(d,"cordial",7)){
    printf("Cordial dans le dico \n");
  }else{
    printf("Cordial est absent du dico\n");
  }

  printf("Testons si bateau est un mot du dico :");
  if(contains_rec(d,"bateau",6)){
    printf("bateau est un mot du dictionnaire\n");
  }else{
    printf("bateau est absent du dico\n");
  }

  destroy_dico(&d);
  return 1;
}
