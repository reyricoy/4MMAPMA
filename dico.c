#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dico.h"




/*---------------------------------------------------------------------------*/
//                               COMMENTAIRES
/*---------------------------------------------------------------------------*/




// dico create_dico()
// {
//   tree arbre;
//   printf("azaazeaze");
//   arbre=(tree)malloc(sizeof(tree));
//   arbre->first=0;
//   arbre->end_of_word=0;
//   arbre->children=NULL;
//   dico dict=(dico)malloc(26*sizeof(tree)); //allocation d'un tableau de 26 arbres
//   for(int i=0;i<NB_KEYS;i++)
//   {
//       dict[i]=arbre;
//   }
//   return dict;
// }
//

/*---------------------------------------------------------------------------*/
//                          CREATION ET SUPPRESSION
/*---------------------------------------------------------------------------*/



 dico create_dico()
 {
   //dico d=malloc(NB_KEYS*sizeof(dico)); // MIEUX vaut faire un calloc direct
   dico d = calloc(NB_KEYS,sizeof(*d));
   if(!d)printf("probleme allocation dico\n");
   //for(int i=0;i<NB_KEYS;i++)d[i]=NULL;

   return d;
 }

void destroy_dico(dico * d)
{
  if(*d==NULL)
  {
    return;
  }
  for(int i=0;i<NB_KEYS;i++)
  {
    if((*d)[i]!=NULL)
    {
        destroy_dico(&(((*d)[i])->children)); // *d[i] devient -> (*d)[i]
        free((*d)[i]);
        //On free tous les sous-dicos, et ensuite on remonte
    }
  }
  free(*d);
}

/*
int nb_children(tree arbre)
{
    if(arbre==NULL){return 0;}

  int compteur;
  for(int i=0;i<NB_KEYS;i++)
  {
    if(arbre[i].children!=NULL)
    {
      compteur++;
    }
  }
  return compteur;
}
*/


/*---------------------------------------------------------------------------*/
//                              COMPTEURS
/*---------------------------------------------------------------------------*/



int nb_children(tree arbre){
    if(arbre==NULL)
        return 0;
    else{
        for(int i = 0; i < NB_KEYS; i++){
            if(arbre[i].children!=NULL)
                return 1;
            else{
                return nb_children(*arbre[i].children);
            }
        }
    }
    return 0;
}


unsigned nb_nodes(dico d)
{
  unsigned noeuds;
  if (d==NULL)
  {
    return 0;
  }
  for(int i=0;i<NB_KEYS;i++)
  {
    noeuds+=nb_nodes(d[i]->children);
  }
  return noeuds+1;
}

unsigned height(dico d)
{
  if (d==NULL)
  {
    return 0;
  }
  unsigned hauteur=height(d[0]->children);
  for(int i=0;i<NB_KEYS;i++)
  {
    hauteur=(hauteur>height(d[i]->children))?hauteur:height(d[i]->children);
  }
  return hauteur;
}


/*---------------------------------------------------------------------------*/
//                          AFFICHAGE
/*---------------------------------------------------------------------------*/


void print_prefix(dico d)
{
  if (d==NULL)
  {
    return;
  }
  else
  {
    for(int i=0;i<NB_KEYS;i++)
    {
      printf("+[%c]%c\n",d[i]->first,d[i]->first);
      if(d[i]->end_of_word==TRUE)
      {
        printf("*");
      }
      printf("\t");
      print_prefix(d[i]->children);
    }
  }
}


/*---------------------------------------------------------------------------*/
//                          COMPARAISONS
/*---------------------------------------------------------------------------*/


bool equals(dico d1, dico d2)
{
  bool test=TRUE;
  if (d1==NULL&&d2==NULL)
  {
    return TRUE;
  }
  else
  {
    for(int i=0;i<NB_KEYS;i++)
    {
      if(d1[i]->first!=d2[i]->first||d1[i]->end_of_word!=d2[i]->end_of_word)
      {
        return FALSE;
      }
      //On teste si tous les enfants du dico verifient la condition
      test=test&&equals(d1[i]->children,d2[i]->children);
    }
    return test;
  }
}

tree create_node(void){
    tree noeud = calloc(1,sizeof(*noeud));
    return noeud;
}


/*---------------------------------------------------------------------------*/
//                          FONCTIONS RECURSIVES
/*---------------------------------------------------------------------------*/
bool contains_rec(dico d, char * word, unsigned size)
{
  if((size == 0) && d[get_index(word[0])]->end_of_word)
  {//si la taille du mot fait 0, il est fini
    return TRUE;
  }
  // si la case est vide c'est qu'il n'y a pas de lettre : out ->
  if(d[get_index(word[0])]==NULL)
    return FALSE;
  // si il y a quelque chose mais que le caractère differt on sort ->
  if(d[get_index(word[0])]->first != word[0])
  {
    return FALSE;
  }
  char suivant[size-1];
  for(int i = 0; i < (size - 1); i++)
  {
    suivant[i] = word[i+1];
  }
  //On avance dans le dico, dans le mot et on reduit la taille
  return contains_rec( (size==0)?d:d[get_index(word[0])]->children, (size==0)? word:suivant, size - 1);
}

bool add_rec(dico d, char * word, unsigned size)
{
  /*if(contains_rec(d,word,size)==TRUE)
  {//Il ne peut pas etre ajoute si il est deja dans le dico
    return FALSE;
  }*/
  if(size == 0)
  {//si la taille du mot est de 0 ça veut dire qu'il a ete ajoute
    return TRUE;
  }
  //int ind = get_index(word[0]);

  if(d[get_index(word[0])] == NULL){
    d[get_index(word[0])]=create_node();
    d[get_index(word[0])]->first=word[0];
    d[get_index(word[0])]->children=create_dico();
  }

  if(size == 1)
  {//si la taille fait 1, le mot est fini donc on le note
    d[get_index(word[0])]->end_of_word = TRUE;
  }
  //On fait la meme chose avec les lettres suivantes du mot
  char suivant[size-1];
  for(int i = 0 ;i < size - 1; i++)
  {
    suivant[i] = word[i+1];
  }
  //On avance dans le dico, dans le mot et on reduit la taille
  return add_rec(d[get_index(word[0])]->children, suivant, size-1);
}

bool remove_rec(dico d, char * word, unsigned size)
{
  //dico temp;
  if(contains_rec(d,word,size)==FALSE)
  {//Il ne peut pas etre enleve si il n'est pas dans le dico
    return FALSE;
  }
  if(size==0)
  {//si la taille du mot est de 0 ça veut dire qu'il a ete enleve
    return TRUE;
  }
  int ind=get_index(word[0]);
  if(d[ind]->first==word[0])
  {//On enleve chaque lettre du mot
    if(nb_children(d[ind])==1)
    {
      destroy_dico(&(d[ind]->children));
      return TRUE;
    }
  }
  if(size==1)
  {//si la taille du mot est de 1 ça veut dire qu'il est fini : pour l
  //enlever il fau retirer le "end_of_word"
    d[ind]->end_of_word=FALSE;
  }
  //On fait la meme chose avec les lettres suivantes du mot
  //char *suivant=(char*)malloc((size-1)*sizeof(char));
  char suivant[size-1];
  for(int i=0;i<size-1;i++)
  {
    suivant[i]=word[i+1];
  }
  //On avance dans le dico, dans le mot et on reduit la taille
  return remove_rec(d[ind]->children,suivant,size-1);
}

/*---------------------------------------------------------------------------*/
//                          FONCTIONS ITERATIVES
/*---------------------------------------------------------------------------*/


/* Recherche d'un mot dans le dictionnaire */
bool contains_iter(dico d, char * word, unsigned size){
    tree tempo;
    for (int i = 0 ; i < size ; i++){
       if (d[get_index(word[i])]==NULL){
           return FALSE;
       }
       if(d[get_index(word[i])]->first == word[i]){
           tempo=d[get_index(word[i])];
           d=d[get_index(word[i])]->children;
       }else{
           return FALSE;
       }
   }
   if(tempo->end_of_word){
       return TRUE;
   }
   else{
       return FALSE;
   }

}



/* Ajout d'un mot dans le dictionnaire */

bool add_iter(dico d, char * word, unsigned size){
    int i=0;
    tree tempo;
    if (contains_iter(d,word,size))
        return FALSE;


    for (i = 0 ; nb_children(d[get_index(word[i])]) >= 1 ; i++){
        d=d[get_index(word[i])]->children;
    }

    for(;i < size; i++){
        d[get_index(word[i])]=create_node();
        d[get_index(word[i])]->first=word[i];
        d[get_index(word[i])]->children=create_dico();
        tempo=d[get_index(word[i])];
        d=d[get_index(word[i])]->children;
    }
    tempo->end_of_word=TRUE;
    return TRUE;
}

/* Suppression d'un mot dans le dictionnaire */
bool remove_iter(dico d, char * word, unsigned size){
    if (!contains_iter(d,word,size))
        return FALSE;
    for (int i = 0 ;  nb_children(d[get_index(word[i])]) != 1 ; i++){
         d=d[get_index(word[i])]->children;
    }
    destroy_dico(&d);
    return TRUE;
}

/*---------------------------------------------------------------------------*/
//                              MAIN
/*---------------------------------------------------------------------------*/



int main()
{
    dico dictionnaire;
    bool test,test2,test3;
    /*TEST POUR LE TRAVAIL 1*/


    //dictionnaire=create_dico();
    //destroy_dico(&dictionnaire);


    /*TEST POUR LE TRAVAIL 4*/


    dictionnaire=create_dico();
    printf("TEST TRAVAIL 4\n");
    test=add_rec(dictionnaire,"bonjour",7);
    //test2=contains_rec(dictionnaire,"bonjour",7);
    //test3=contains_rec(dictionnaire,"bon",3);
    printf("Les tests : [%d][%d][%d]\n",test,test2,test3);

    /*Test Pour L'itératif */
    //destroy_dico(&dictionnaire);
 //   dictionnaire=create_dico();
 //   test =add_iter(dictionnaire,"bonsoir", 7);
 //   printf("\n le test a été réussi : %d",test);
 //   test =add_iter(dictionnaire,"bonsoir", 7);
 //   printf("\n le test a été réussi : %d",test);
 //   test=contains_iter(dictionnaire,"bonsoir",7);
//    printf("\n le dictionnaire contient t'il bonsoir ? : %d",test);
  //  remove_iter(dictionnaire,"bonsoir",7);
  //  test=contains_iter(dictionnaire,"bonsoir",7);
 //   printf("\n le dico contient t'il bonsoir ? : %d \n",test);
}
