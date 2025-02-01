#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
  int value;
  Node * next;
};

Node * Node_alloc(int value) {
  /* TODO : allouer un maillon d'un liste chaînée */
}

void Node_free(Node ** liste) {
  /* TODO : libérer une liste chaînée */
}

int Node_ajouter(Node ** liste, int value) {
  /* TODO : ajouter un élément à une liste chaînée */
}

void Node_afficher(const Node * liste) {
  printf("[");
  /* TODO : afficher les éléments de la liste chaînée */
  printf("]\n");
}

int main() {
  Node * liste = NULL;
  int valeurs[] = {1, 2, 3, 4, -1};
  int i;
  for(i = 0; valeurs[i] >= 0; ++i) {
    if(! Node_ajouter(&liste, valeurs[i])) {
      Node_free(&liste);
      fprintf(stderr, "Erreur ajout liste : arrêt.\n");
      exit(EXIT_FAILURE);
    }
  }
  Node_afficher(liste);
  Node_free(&liste);
  exit(EXIT_SUCCESS);
}