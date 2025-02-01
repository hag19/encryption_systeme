/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 116.
 */

#ifndef DEF_HEADER_TREE
#define DEF_HEADER_TREE

#include <stdio.h>

typedef struct Node Node;
struct Node {
  char key;
  int value;
  Node * lower;
  Node * upper;
  Node * next;
  Node * prev;
};

Node * Node_alloc(char key, int value);

void Node_free(Node ** node);

int Node_ajouter_chaine(Node ** node, const char * chaine);

void Node_afficher(FILE * flow, const Node * node);

void Node_afficher_all(FILE * flow, const Node * node);

#endif