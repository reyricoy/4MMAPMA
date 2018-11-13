#include "dico.h"

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
 dico create_dico()
 {
   dico d=malloc(NB_KEYS*sizeof(dico));
   if(!d)printf("probleme allocation dico\n");
   for(int i=0;i<NB_KEYS;i++)d[i]=NULL;
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
        destroy_dico(&((*d[i])->children));
        free((*d)[i]);
        //On free tous les sous-dicos, et ensuite on remonte
    }
  }
  free(*d);
}


unsigned nb_children(tree arbre)
{
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

bool contains_rec(dico d, char * word, unsigned size)
{
  if(size==0)
  {//si la taille du mot fait 0, il est fini
    return TRUE;
  }
  int ind=get_index(word[0]);
  if(d[ind]->first!=word[0])
  {//Si un caractere differt, on retourne FALSE
    return FALSE;
  }
  char *suivant=(char*)malloc((size-1)*sizeof(char));
  for(int i=0;i<size-1;i++)
  {
    suivant[i]=word[i+1];
  }
  //On avance dans le dico, dans le mot et on reduit la taille
  return contains_rec(d[ind]->children,suivant,size-1);
}

bool add_rec(dico d, char * word, unsigned size)
{
  if(contains_rec(d,word,size)==TRUE)
  {//Il ne peut pas etre ajoute si il est deja dans le dico
    return FALSE;
  }
  if(size==0)
  {//si la taille du mot est de 0 ça veut dire qu'il a ete ajoute
    return TRUE;
  }

  int ind=get_index(word[0]);
  if(d[ind]->first!=word[0])
  {//On rajoute chaque lettre du mot au bon endroit
    d[ind]->first=word[0];
  }
  if(size==1)
  {//si la taille fait 1, le mot est fini donc on le note
    d[ind]->end_of_word=TRUE;
  }
  //On fait la meme chose avec les lettres suivantes du mot
  char *suivant=(char*)malloc((size-1)*sizeof(char));
  for(int i=0;i<size-1;i++)
  {
    suivant[i]=word[i+1];
  }
  //On avance dans le dico, dans le mot et on reduit la taille
  return add_rec(d[ind]->children,suivant,size-1);
}

bool remove_rec(dico d, char * word, unsigned size)
{
  dico temp;
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
  char *suivant=(char*)malloc((size-1)*sizeof(char));
  for(int i=0;i<size-1;i++)
  {
    suivant[i]=word[i+1];
  }
  //On avance dans le dico, dans le mot et on reduit la taille
  return remove_rec(d[ind]->children,suivant,size-1);
}


bool contains_iter(dico d, char * word, unsigned size){
    for (int i = 0 ; i < size ; i++){
        if(d[get_index(word[i])]->first == word[i]){
            d=d[get_index(word[i])]->children;
        }else{
            return FALSE;
        }
    }
    return TRUE;

}



/* size est la taille du mot word */
bool add_iter(dico d, char * word, unsigned size){
    if (!contains_iter(d,word,size))
        return FALSE;


    for (int i = 0 ; i<size || nb_children(d[get_index(word[i])] != 1) ; i++){
        d=d[get_index(word[i])]->children;
    }
    for(;i < size; i++){
        d[get_index(word[i])]->children=create_dico();
        d=d[get_index(word[i])]->children;
        d[get_index(word[i])]->first=word[i];
    }
    d[get_index(word[i])]->end_of_word=TRUE;
    return TRUE;
}

bool remove_iter(dico d, char * word, unsigned size){


}

int main()
{
  dico dictionnaire;
  /*TEST POUR LE TRAVAIL 1*/


    dictionnaire=create_dico();
    destroy_dico(&dictionnaire);


  /*TEST POUR LE TRAVAIL 4*/


  dictionnaire=create_dico();
  printf("TEST TRAVAIL 4\n");
  bool test=add_rec(dictionnaire,"Bonjour",7);
  printf("Le test a été réussi : %d\n",test);
}

