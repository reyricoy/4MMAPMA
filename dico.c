#include "dico.h"

dico create_dico()
{
  dico dict=calloc(NB_KEYS,sizeof(tree));  //allocation d'un tableau de 26 arbres
  return dict;
}


void destroy_dico(dico * d)
{
  if(d==NULL)
  {
    return;
  }
  for(int i=0;i<NB_KEYS;i++)
  {
    destroy_dico(&((*d[i])->children)); //On free tous les sous-dicos, et ensuite on remonte
  }
  free(d);
}

//test
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

int main()
{
  dico dictionnaire;
  dictionnaire=create_dico();
  printf("oui");
  node noeud;
  noeud.first='a';
  noeud.end_of_word=TRUE;
  noeud.children=NULL;
  printf("oui");
  dictionnaire[0]=&noeud;
  printf("oui");
  node noeud2;
  noeud2.first='b';
  noeud2.end_of_word=FALSE;
  noeud2.children=create_dico();
  dictionnaire[1]=&noeud2;
  node noeud3;
  noeud3.first='a';
  noeud3.end_of_word=TRUE;
  noeud3.children=NULL;
  (dictionnaire[1]->children)[0]=&noeud3;
  destroy_dico(&dictionnaire);
}
