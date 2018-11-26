#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dico.h"




/*---------------------------------------------------------------------------*/
//                               COMMENTAIRES
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
//                          CREATION ET SUPPRESSION
/*---------------------------------------------------------------------------*/

 dico create_dico()
 {
   dico d = calloc(NB_KEYS,sizeof(*d));
   if(!d)printf("probleme allocation dico\n");
   return d;
 }


int destroy_dico(dico * d)
{
  if(*d==NULL)
  {
    return 1;
  }
  for(int i=0;i<NB_KEYS;i++)
  {
    if((*d)[i]!=NULL)
    {
        return destroy_dico(&(((*d)[i])->children)); // *d[i] devient -> (*d)[i]
        free((*d)[i]);
        //On free tous les sous-dicos, et ensuite on remonte
    }
  }
  free(*d);
}


/*---------------------------------------------------------------------------*/
//                              COMPTEURS
/*---------------------------------------------------------------------------*/



int nb_children(tree arbre){
    if(arbre==NULL)
        return 0;
    else{
        for(int i = 0; i < NB_KEYS; i++){
            if(arbre[i].children==NULL)
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
  print_prefix_aux(d,0);
}

void print_prefix_aux(dico d,int it)
{
  if (d==NULL)
  {
    return;
  }
  else
  {
    for(int i=0;i<NB_KEYS;i++)
    {
      if(d[i]!=NULL)
      {
        for(int j=0;j<it;j++)
        {
          printf("+ ");
        }
        printf("[%c]%c",d[i]->first,d[i]->first);
        if(d[i]->end_of_word==TRUE)
        {
          printf("*");
        }
        printf("\n");
        print_prefix_aux(d[i]->children,it+1);
      }
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
      if(d2[i]!=NULL&&d1[i]!=NULL)
      {
        if(d1[i]->first!=d2[i]->first||d1[i]->end_of_word!=d2[i]->end_of_word)
        {
          return FALSE;
        }
        //On teste si tous les enfants du dico verifient la condition
        test=test&&equals(d1[i]->children,d2[i]->children);
      }
      if(((d1[i]==NULL &&d2[i]!=NULL) ||(d2[i]==NULL &&d1[i]!=NULL)))
      {
        return FALSE;
      }

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
  if((size == 0) )
  {//si la taille du mot fait 0, il est fini
    return TRUE;
  }
  if((size == 1) && d[get_index(word[0])]->end_of_word)
  {//si la taille du mot fait 1,et qu'il y a end_of_word il est fini
    return TRUE;
  }
  if((size == 1) && (!d[get_index(word[0])]->end_of_word))
  {//si la taille du mot fait 1,et qu'il n'y a pas end_of_word, le mot n'y ai pas
    return FALSE;
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
  if(d[ind]->first==word[0]&&size!=1)
  {//On enleve chaque lettre du mot
    if(nb_words(d[ind]->children)==1)
    {
      dico temporaire=d[ind]->children;
      destroy_dico(&(temporaire));
      tree temp=d[ind];
      free(temp);
      d[ind]=NULL;
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
//                     NOMBRE DE MOTS ET PRINT DICO
/*---------------------------------------------------------------------------*/


unsigned nb_words(dico d)
{
  int nombre=0;
  if (d==NULL)
  {
    return 0;
  }
  else
  {
    for(int i=0;i<NB_KEYS;i++)
    {
      if(d[i]!=NULL)
      {
        if(d[i]->end_of_word==TRUE)
        {
          nombre+=nb_words(d[i]->children)+1;
        }
        else
        {
          nombre+=nb_words(d[i]->children);
        }
      }
    }
  }
  return nombre;
}


list print_dico_aux(dico d, list l, char* mot)          //cree liste contenant tout les mots du dico
{
    unsigned i;
    char* copie = calloc(512,sizeof(char));
    for(i=0;i<NB_KEYS;i++)
    {
        if(d[i]!=NULL)
        {
            strcpy(copie,mot);
            strncat(copie,&(d[i]->first),1);
            //strncat(copie,"\0",1);
            if(d[i]->end_of_word){
              l=add_mot(copie,l);
            }
            l = print_dico_aux(d[i]->children,l,copie);
        }
    }
    free(copie);
    return l;
}

void print_dico(dico d)                 //imprimme tout les mots du dico
{
    list l = create_list();
    char* mot = calloc(512,sizeof(char));
    l = print_dico_aux(d,l,mot);
    print_list(l);
    free(mot);
    free_list(l);
}


/************ LISTES ************/

list create_list() {
    list liste=calloc(1,sizeof(*liste));
    liste->next=NULL;
    liste->word=" ";
    liste->taille=0;
    return liste;
}

/* insertion de l'element en tete de liste */
list add_mot(char* mot, list l)
{
    if(strlen(mot)==0) return l;  //si mot vide on fait rien
    if(!l)
    {
        l=calloc(1,sizeof(*l));
        l->word=calloc(128,sizeof(char));
        if(strcpy(l->word,mot)) return l;
    }
    list ptr_sur_l = l;
    while(l->next != NULL) l=l->next;
    list p = calloc(1,sizeof(*p));
    p->word = calloc(128,sizeof(char));
    strcpy(p->word,mot);
    l->next = p;
    return ptr_sur_l;
}


void print_list(list l)
{
  while(l!=NULL)
  {

    printf("%s",l->word);
    printf("\n");
    l=l->next;
  }
}

void free_list(list l)
{
  list temp;
  while(l!=NULL)
  {
    temp=l;
    l=l->next;
    free(temp);
  }
}



/*---------------------------------------------------------------------------*/
//                              MAIN
/*---------------------------------------------------------------------------*/



int main()
{
    dico dictionnaire,dictionnaire1,dictionnaire2;
    bool test,test2,test3,test4,test5;
    int nb_mots;
    /*TEST POUR LE TRAVAIL 1*/


    //dictionnaire=create_dico();
    //destroy_dico(&dictionnaire);

    /*TEST POUR LE TRAVAIL 2*/

    // dictionnaire1=create_dico();
    // dictionnaire2=create_dico();
    // printf("TEST TRAVAIL 1\n");
    // test=equals(dictionnaire1,dictionnaire2);
    // add_rec(dictionnaire1,"bonjour",7);
    // test3=equals(dictionnaire1,dictionnaire2);
    // add_rec(dictionnaire2,"bonjour",7);
    // test2=equals(dictionnaire1,dictionnaire2);
    // printf("Les dictionnaires sont égaux au debut [%d] a la fin [%d]\n Et milieu [%d]\n",test,test2,test3);
    // //Si les tests fonctionnent on a : 1 1 0
    // destroy_dico(&dictionnaire1);
    // destroy_dico(&dictionnaire2);

    /*TEST POUR LE TRAVAIL 4*/

    /*Test Pour Le Récursif */

    // dictionnaire=create_dico();
    // printf("TEST TRAVAIL 4\n");
    // test=add_rec(dictionnaire,"bonjour",7);
    // test2=contains_rec(dictionnaire,"bonjour",7);
    // test3=contains_rec(dictionnaire,"bon",3);
    // add_rec(dictionnaire,"bonsoir",7);
    // print_prefix(dictionnaire);
    // nb_mots=nb_words(dictionnaire);
    // remove_rec(dictionnaire,"bonjour",7);
    // test4=contains_rec(dictionnaire,"bonjour",7);
    // printf("Les tests : [%d][%d][%d][%d]\nIl y a [%d] mots dans le dico\n",test,test2,test3,test4,nb_mots);
    // destroy_dico(&dictionnaire);


    /*Test Pour L'itératif */

   // dictionnaire=create_dico();
   // test =add_iter(dictionnaire,"bonsoir", 7);
   // printf("\n le test a été réussi : %d",test);
   // test =add_iter(dictionnaire,"bonsoir", 7);
   // printf("\n le test a été réussi : %d",test);
   // test=contains_iter(dictionnaire,"bonsoir",7);
   // printf("\n le dictionnaire contient t'il bonsoir ? : %d",test);
   // remove_iter(dictionnaire,"bonsoir",7);
   // test=contains_iter(dictionnaire,"bonsoir",7);
   // printf("\n le dico contient t'il bonsoir ? : %d \n",test);

 // TEST TRAVAIL 5 : IMPRESSION DU DICO
    dictionnaire=create_dico();
    add_rec(dictionnaire,"bonjour",7);
    add_rec(dictionnaire,"bon",3);
    add_rec(dictionnaire,"bonsoir",7);
    print_prefix(dictionnaire);

    remove_rec(dictionnaire,"bon",3);
    print_prefix(dictionnaire);

    print_dico(dictionnaire);
    destroy_dico(&dictionnaire);
}
