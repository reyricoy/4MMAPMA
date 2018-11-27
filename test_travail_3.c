#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dico.h"




void test_3(dico d){

  printf("debut test3\n");
  add_iter(d,"bonsoir",7);

  add_iter(d,"bon",3);
  add_iter(d,"bord",4);
  add_iter(d,"bordeau",7);
  add_iter(d,"bonjour",7);
  add_iter(d,"bonsoir",7);
  add_iter(d,"cordial",7);
  add_iter(d,"cordialement",12);

 add_iter(d,"demain",6);

 add_iter(d,"demander",8);
  add_iter(d,"manger",6);
  add_iter(d,"vivre",5);
 add_iter(d,"boire",5);

  print_prefix(d);

  printf("Retirons maintenant les mots en c :\n");
  remove_iter(d,"cordial",7);
  //remove_iter(d,"cordialement",12);

  print_prefix(d);

  printf("Tester si cordial est toujours là :");
  if(contains_iter(d,"cordial",7)){
    printf("Cordial est toujours là\n");
  }else{
    printf("Cordial est absent du dico\n");
  }
  printf("Tester si Boire est un mot du dico :");
  if(contains_iter(d,"boire",5)){
    printf("Boire est un mot du dictionnaire\n");
  }else{
    printf("Boire est absent du dico\n");
  }

  destroy_dico(&d);
}
