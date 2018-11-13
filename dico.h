#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0


struct node {
    char first;
    bool end_of_word;
    struct node ** children;
};
typedef struct node  node;
typedef struct node * tree;
typedef struct node ** dico;

#define NB_KEYS 26
unsigned get_index(char c) { return c - 'a'; }
char get_char(unsigned index) { return index + 'a'; }



/*//************TRAVAIL 1************\\*/
// construction
dico create_dico();
//destruction
void destroy_dico(dico * d);


/*//************TRAVAIL 2************\\*/

/** mesures */
unsigned nb_children(tree arbre);
unsigned nb_nodes(dico d);
unsigned height(dico d);
void print_prefix(dico d);
bool equals(dico d1, dico d2);


/*//************TRAVAIL 3************\\*/
bool contains_rec(dico d, char * word, unsigned size);
bool add_rec(dico d, char * word, unsigned size);
bool remove_rec(dico d, char * word, unsigned size);

