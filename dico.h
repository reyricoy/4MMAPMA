#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0

/********STRUCTURE DU DICO********/
struct node {
    char first;
    bool end_of_word;
    struct node ** children;
};
typedef struct node  node;
typedef struct node * tree;
typedef struct node ** dico;

#define NB_KEYS 26
unsigned get_index(char c);
char get_char(unsigned index);

/********STRUCTURE DES LISTES********/

struct cell {
    char* word;
    int taille;
    struct cell * next;
};

typedef struct cell * list;

list create_list() ;
void print_list(list l);
void free_list(list l);
list add_mot(char* mot, list l);

/********STRUCTURE ITERATEUR ********/

struct _iterator_info {
    tree t;
    int index_word;
};
typedef struct _iterator_info iterator_info;
struct _iterator {
    char * word;
     iterator_info * stack;
    int index_stack;
};

typedef struct _iterator iterator;

/*************TRAVAIL 1*************/

// construction
dico create_dico();
//destruction
int destroy_dico(dico * d);


/*************TRAVAIL 2************\\*/

/** mesures */
int nb_children(tree arbre);
unsigned nb_nodes(dico d);
unsigned height(dico d);
void print_prefix(dico d );
void print_prefix_aux(dico d,int it);
bool equals(dico d1, dico d2);
tree create_tree();

/*************TRAVAIL 3************\\*/
bool contains_iter(dico d, char * word, unsigned size);
/* size est la taille du mot word */
bool add_iter(dico d, char * word, unsigned size);
bool remove_iter(dico d, char * word, unsigned size);


/*************TRAVAIL 4************\\*/
bool contains_rec(dico d, char * word, unsigned size);
bool add_rec(dico d, char * word, unsigned size);
bool remove_rec(dico d, char * word, unsigned size);


/*************TRAVAIL 5************\\*/
unsigned nb_words(dico d);
void print_dico(dico d);
list print_dico_aux(dico d,list words_list,char* word_incomplete);


/*************TRAVAIL 6************\\*/
iterator * start_iterator(dico d);
void destroy_iterator(iterator ** it);
bool has_next(iterator * it);
char * next (iterator * it);
