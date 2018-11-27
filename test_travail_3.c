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


int test3(){
  printf("\n");
  printf("TEST 3 : \n");
  dico d = create_dico();

  add_iter(d,"ours",4);
  add_iter(d,"ourson",6);
  add_iter(d,"oursonne",8);
  add_iter(d,"ourse",5);
  add_iter(d,"brule",5);
  add_iter(d,"brille",6);
  add_iter(d,"bord",4);
  add_iter(d,"bordeau",7);
  add_iter(d,"bateau",6);
  add_iter(d,"bonsoir",7);

  print_prefix(d);
  print_dico(d);

  printf("\n");
  printf("Retirons maintenant les mots en c :\n");
  printf("Cette fonction ne fonctionne pas pour le moment\n");
  printf("\n");

/*  remove_iter(d,"cordial",7);
  remove_iter(d,"bonjour",7);
  remove_iter(d,"cordialement",12);
  print_prefix(d);
*/
  printf("Testons si cordial est dans le dico :");
  if(contains_iter(d,"cordial",7)){
    printf("Cordial est toujours là\n");
  }else{
    printf("Cordial est absent du dico\n");
  }

  printf("Testons si bateau est un mot du dico :");
  if(contains_iter(d,"bateau",6)){
    printf("bateau est un mot du dictionnaire\n");
  }else{
    printf("bateau est absent du dico\n");
  }



  destroy_dico(&d);
  return 1;
}
