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
unsigned get_index(char c) { return c - 'a'; }
char get_char(unsigned index) { return index + 'a'; }


 dico create_dico()
 {
   dico d = calloc(NB_KEYS,sizeof(*d));
   if(!d)printf("probleme allocation dico\n");
   return d;
 }

 tree create_tree()
 {
   tree t = calloc(1,sizeof(*t));
   if(!t)printf("probleme allocation tree\n");
   return t;
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
      if((*d)[i]->children!=NULL)
      {
        destroy_dico(&(((*d)[i])->children)); // *d[i] devient -> (*d)[i]
        free((*d)[i]);
        (*d)[i]=NULL;
        //On free tous les sous-dicos, et ensuite on remonte
      }
    }
  }
  free(*d);
  *d=NULL;

  return 1;
}


/*---------------------------------------------------------------------------*/
//                              COMPTEURS
/*---------------------------------------------------------------------------*/



int nb_children(tree arbre){
    int cpt=0;
    if(arbre==NULL)
        return 0;
    else{
        for(int i = 0; i < NB_KEYS; i++){
            if(arbre->children[i] != NULL)
                cpt++;
        }
    }
    return cpt;
}


unsigned nb_nodes(dico d)
{
  unsigned noeuds=0,compteur=0;
  if (d==NULL)
  {
    return 0;
  }
  for(int i=0;i<NB_KEYS;i++)
  {
    if (d[i]==NULL)
    {
      compteur++;
    }
  }
  if (compteur==NB_KEYS)return 0;
  for(int i=0;i<NB_KEYS;i++)
  {
    if (d[i]!=NULL)
    {
      noeuds+=nb_nodes(d[i]->children);
    }
  }
  return noeuds+1;
}

unsigned height(dico d)
{
  if (d==NULL)
  {
    return 0;
  }
  int compteur=0;
  int hauteur =0;
  for(int i=0;i<NB_KEYS;i++)
  {
    if (d[i]==NULL)
    {
      compteur++;
    }
  }
  if (compteur==NB_KEYS)return 0;
  for(int i=0;i<NB_KEYS;i++)
  {
    if (d[i]!=NULL)
    {
      hauteur=(hauteur>height(d[i]->children))?hauteur:height(d[i]->children);
    }
  }
  return hauteur+1;
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
    tree noeud = malloc(sizeof(*noeud));
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
    if(nb_words(d)==1)
    {
      destroy_dico(&d);
      return TRUE;
    }
    if(nb_words(d[ind]->children)==1)
    {
      dico temporaire=d[ind]->children;
      destroy_dico(&(temporaire));
      return TRUE;
    }
  }
  if(size==1)
  {//si la taille du mot est de 1 ça veut dire qu'il est fini : pour l
  //enlever il faut retirer le "end_of_word"
    d[ind]->end_of_word=FALSE;
    if(nb_words(d[ind]->children)==0)
    {
      destroy_dico(&d[ind]->children);
      free(d[ind]);
      d[ind]=NULL;
      return TRUE;
    }
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

    for (int i = 0 ; i < size ; i++){
      if (d[get_index(word[i])]==NULL){
          return FALSE;
      }
    if(d[get_index(word[i])]->first == word[i]){
           if(i!= size-1){
             d=d[get_index(word[i])]->children;
           }
       }else{
           return FALSE;
       }
   }
   if(d[get_index(word[size-1])]->end_of_word){
       return TRUE;
   }
   else{
       return FALSE;
   }

}



/* Ajout d'un mot dans le dictionnaire */

bool add_iter(dico d, char * word, unsigned size){
    int i=0;
    if(d==NULL){
      return FALSE;
    }
    if (contains_iter(d,word,size))
        return FALSE;

    for(i=0;i < size; i++){
      if (d[get_index(word[i])]==NULL){
        d[get_index(word[i])]=create_node();
        d[get_index(word[i])]->first=word[i];
        d[get_index(word[i])]->children=create_dico();
      }

      if (i==(size-1)){
          d[get_index(word[i])]->end_of_word=TRUE;
      }
      d=d[get_index(word[i])]->children;
    }
    return TRUE;
}


/* Suppression d'un mot dans le dictionnaire */
bool remove_iter(dico d, char * word, unsigned size){
  int i;
    if (!contains_iter(d,word,size))
        return FALSE;
    for (i = 0 ;  nb_children(d[get_index(word[i])]) != 1 ; i++){
         d=d[get_index(word[i])]->children;
    }
    destroy_dico(&d[get_index(word[i])]->children);
    free(d[get_index(word[i])]);
    d[get_index(word[i])]=NULL;
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

/******************* ITERATEUR ****************/

iterator * start_iterator(dico d){
  // il doit contenir dans
  /*
  struct iterator_info {
      tree t; <- tous les arbres avec estampille 0
      int index_word; estampille
  };

  struct _iterator {
      char * word; <- le mot initiallement NULL
      struct iterator_info * stack; la pile d'arbres
      int index_stack; <- le nombre d'arbres Nb nb_nodes
  };

  typedef struct _iterator iterator;

  il doit retourner un pointeur d'iterator

  */

  iterator * it = calloc(1,sizeof(*it));
  if(it==NULL)
  {
    printf("Erreur allocation iterateur\n");
    return NULL;
  }
  it->word = calloc(height(d)+1,sizeof(char));
  if(it->word==NULL)
  {
    printf("Erreur allocation word iterateur\n");
    return NULL;
  }
  it->stack = calloc(nb_nodes(d),sizeof( iterator_info));
  if(it->stack==NULL)
  {
    printf("Erreur allocation stack iterateur\n");
    return NULL;
  }
  it->index_stack=-1;
  for(int i = NB_KEYS-1; i >= 0 ; i-- ){
    if(d[i] != NULL){
        it->stack[it->index_stack+1].t = d[i];
        it->stack->index_word = 0;
        it->index_stack++;

    }
  }

  return it;
}

void destroy_iterator(iterator ** it){
  free((*it)->stack);
  free((*it)->word);
  free(*it);
}

bool has_next(iterator * it){
    if(it->index_stack == -1)
      return FALSE;

    return TRUE;
}
char * next (iterator * it){
  while(it->stack[it->index_stack].t->end_of_word == 0){
    it->word[it->stack[it->index_stack].index_word] = it->stack[it->index_stack].t->first;
    it->word[it->stack[it->index_stack].index_word+1] = '\0';
    tree arbre=it->stack[it->index_stack].t;
    it->stack[it->index_stack].index_word++;
    int index_word_mem=it->stack[it->index_stack].index_word;
    it->index_stack--;
    for(int i = NB_KEYS-1 ; i != 0 ; i--){
      if(arbre->children[i] != NULL){
        it->index_stack++;
        it->stack[it->index_stack].t = arbre->children[i];
        it->stack[it->index_stack].index_word=index_word_mem;
      }
    }
  }
  if(it->stack[it->index_stack].t->end_of_word == 1)
  {
    it->word[it->stack[it->index_stack].index_word] = it->stack[it->index_stack].t->first;
    it->word[it->stack[it->index_stack].index_word+1]='\0';
    tree arbre=it->stack[it->index_stack].t;
    it->stack[it->index_stack].index_word++;
    int index_word_mem=it->stack[it->index_stack].index_word;
    it->index_stack--;
    for(int i = 26 ; i != 0 ; i--){
      if(arbre->children[i] != NULL){
        it->index_stack++;
        it->stack[it->index_stack].t = arbre->children[i];
        it->stack[it->index_stack].index_word=index_word_mem;
      }
    }
  }
  return it->word;
}

/*---------------------------------------------------------------------------*/
//                              MAIN
/*---------------------------------------------------------------------------*/



int main()
{

  test1();
  test2();
  test3();
  test4();
  //test5();
  test6();
  printf("\n");
  menu();

//     dico dictionnaire,dictionnaire1,dictionnaire2;
//     bool test,test2,test3,test4,test5;
//     int nb_mots;
//     /*TEST POUR LE TRAVAIL 1*/
//
//
//     //dictionnaire=create_dico();
//     //destroy_dico(&dictionnaire);
//
//     /*TEST POUR LE TRAVAIL 2*/
//
//     // dictionnaire1=create_dico();
//     // dictionnaire2=create_dico();
//     // printf("TEST TRAVAIL 1\n");
//     // test=equals(dictionnaire1,dictionnaire2);
//     // add_rec(dictionnaire1,"bonjour",7);
//     // test3=equals(dictionnaire1,dictionnaire2);
//     // add_rec(dictionnaire2,"bonjour",7);
//     // test2=equals(dictionnaire1,dictionnaire2);
//     // printf("Les dictionnaires sont égaux au debut [%d] a la fin [%d]\n Et milieu [%d]\n",test,test2,test3);
//     // //Si les tests fonctionnent on a : 1 1 0
//     // destroy_dico(&dictionnaire1);
//     // destroy_dico(&dictionnaire2);
//
//     /*TEST POUR LE TRAVAIL 4*/
//
//     /*Test Pour Le Récursif */
//
//     dictionnaire=create_dico();
//     printf("TEST TRAVAIL 4\n");
//     test=add_rec(dictionnaire,"ours",4);
//     add_rec(dictionnaire,"ourson",6);
//     add_rec(dictionnaire,"oursonne",8);
//     add_rec(dictionnaire,"ourse",5);
//     add_rec(dictionnaire,"brule",5);
//     add_rec(dictionnaire,"brille",6);
//     add_rec(dictionnaire,"bord",4);
//     add_rec(dictionnaire,"bordeau",7);
//     add_rec(dictionnaire,"bateau",6);
//     add_rec(dictionnaire,"bonsoir",7);
//     test=remove_rec(dictionnaire,"ourse",5);
//
//     // print_prefix(dictionnaire);
//     // nb_mots=nb_words(dictionnaire);
//     // printf("Les tests : [%d][%d][%d][%d]\nIl y a [%d] mots dans le dico\n",test,test2,test3,test4,nb_mots);
//     // destroy_dico(&dictionnaire);
//
//
//     /*Test Pour L'itératif */
//
//    // dictionnaire=create_dico();
//    // test =add_iter(dictionnaire,"bonsoir", 7);
//    // printf("\n le test a été réussi : %d",test);
//    // test =add_iter(dictionnaire,"bonsoir", 7);
//    // printf("\n le test a été réussi : %d",test);
//    // test=contains_iter(dictionnaire,"bonsoir",7);
//    // printf("\n le dictionnaire contient t'il bonsoir ? : %d",test);
//    // remove_iter(dictionnaire,"bonsoir",7);
//    // test=contains_iter(dictionnaire,"bonsoir",7);
//    // printf("\n le dico contient t'il bonsoir ? : %d \n",test);
//
//  // TEST TRAVAIL 5 : IMPRESSION DU DICO
//    //  dictionnaire=create_dico();
//    //  add_rec(dictionnaire,"bonjozy",7);
//    //  add_rec(dictionnaire,"bon",3);
//    //   // add_rec(dictionnaire,"co",2);
//    // add_rec(dictionnaire,"bonsoiw",7);
//    // add_rec(dictionnaire,"coucou",6);
//    //  print_prefix(dictionnaire);
//    //
//    //  // remove_rec(dictionnaire,"b",3);
//    //  print_prefix(dictionnaire);
//    //
//    //  print_dico(dictionnaire);
//
//    test_3();
//
// // TEST TRAVAIL 6 : ITERATEUR :
// // appeler une fonction test ici.


}
